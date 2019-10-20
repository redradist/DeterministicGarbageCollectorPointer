#!/usr/bin/env python3

import os
import re
import json
import sys
from pathlib import Path
from typing import List, Set, Dict

from clang.cindex import *
from ctypes.util import find_library

Config.set_library_file('/usr/lib/llvm-7/lib/libclang.so.1')

import clang.cindex


def get_lexical_parents(cursor):
    parents = []
    if hasattr(cursor, 'lexical_parent'):
        parent_iter = cursor.lexical_parent
        while hasattr(parent_iter, 'kind') and \
              (parent_iter.kind == CursorKind.NAMESPACE or \
               parent_iter.kind == CursorKind.CLASS_DECL):
            parents.append((parent_iter.kind, parent_iter))
            parent_iter = parent_iter.lexical_parent
    return list(reversed(parents))


class ClassDecl:
    def __init__(self, cursor):
        self.class_decl = cursor
        spelling_type = cursor.spelling
        record_type = re.search(r'(const)?\s?(?P<type_name>[_A-Za-z][_A-Za-z0-9]*)', spelling_type)
        if record_type:
            self.class_name = record_type.group('type_name')
        else:
            self.class_name = spelling_type
        self.base_decls = ClassDecl.get_base_classes(self.class_decl)
        self.field_decl = ClassDecl.get_field_decls(self.class_decl)
        record_type = re.search(r'(const)?\s?(?P<type_name>[_A-Za-z][_A-Za-z0-9]*)', spelling_type)
        if record_type:
            self.class_name = record_type.group('type_name')
        else:
            self.class_name = spelling_type
        self.parents = get_lexical_parents(cursor)

    def __eq__(self, other):
        return self.class_name == other.class_name and self.parents == other.parents

    def __ne__(self, other):
        return not self.__eq__(other)

    def __hash__(self):
        hash_sum = hash(self.class_name)
        for item in self.parents:
            hash_sum ^= hash(item[0].value)
            hash_sum ^= hash(item[1].spelling)
        return hash_sum

    def __repr__(self):
        text = f"class file={self.class_decl.location.file}, line=({self.class_decl.extent.start.line}:{self.class_decl.extent.start.column}, {self.class_decl.extent.end.line}:{self.class_decl.extent.end.column});"
        return text

    @property
    def file(self):
        return self.class_decl.location.file

    @property
    def lines(self):
        return (self.class_decl.extent.start.line,
                self.class_decl.extent.start.column,
                self.class_decl.extent.end.line,
                self.class_decl.extent.end.column)

    @staticmethod
    def get_base_classes(class_decl):
        bases = []
        if hasattr(class_decl, 'get_children'):
            for child in class_decl.get_children():
                if child.kind == clang.cindex.CursorKind.CXX_BASE_SPECIFIER:
                    bases.append(child)
        return bases

    @staticmethod
    def get_field_decls(class_decl):
        field_decls = []
        if hasattr(class_decl, 'get_children'):
            for child in class_decl.get_children():
                if child.kind == clang.cindex.CursorKind.FIELD_DECL:
                    field_decls.append(child)
        return field_decls


class MemberClassUsedGCPtrClassDecl:
    def __init__(self, cursor, class_used_class_used_gc_ptr, class_used_gc_ptr):
        self.member_name = cursor.spelling
        self.class_used_class_used_gc_ptr = class_used_class_used_gc_ptr
        self.class_used_gc_ptr = class_used_gc_ptr
        self.parents = get_lexical_parents(cursor)

    def __eq__(self, other):
        return self.member_name == other.member_name and self.parents == other.parents

    def __hash__(self):
        hash_sum = hash(self.member_name)
        for item in self.parents:
            hash_sum ^= hash(item[1].spelling)
        return hash_sum

    def __repr__(self):
        text = ''
        for item in self.parents:
            if item[0] == CursorKind.NAMESPACE:
                text += f"namespace file={item[1].location.file}, line=({item[1].extent.start.line}:{item[1].extent.start.column}, {item[1].extent.end.line}:{item[1].extent.end.column});"
            elif item[0] == CursorKind.CLASS_DECL:
                text += f"class file={item[1].location.file}, line=({item[1].extent.start.line}:{item[1].extent.start.column}, {item[1].extent.end.line}:{item[1].extent.end.column});"
        return text

    @property
    def file(self):
        return self.class_used_gc_ptr.file

    @property
    def lines(self):
        return self.class_used_gc_ptr.lines


class GCPtrMemberClassDecl:
    def __init__(self, cursor):
        self.member_name = cursor.spelling
        self.parents = get_lexical_parents(cursor)

    def __eq__(self, other):
        return self.member_name == other.member_name and self.parents == other.parents

    def __hash__(self):
        hash_sum = hash(self.member_name)
        for item in self.parents:
            hash_sum ^= hash(item[1].spelling)
        return hash_sum

    def __repr__(self):
        text = ''
        for item in self.parents:
            if item[0] == CursorKind.NAMESPACE:
                text += f"namespace file={item[1].location.file}, line=({item[1].extent.start.line}:{item[1].extent.start.column}, {item[1].extent.end.line}:{item[1].extent.end.column});"
            elif item[0] == CursorKind.CLASS_DECL:
                text += f"class file={item[1].location.file}, line=({item[1].extent.start.line}:{item[1].extent.start.column}, {item[1].extent.end.line}:{item[1].extent.end.column});"
        return text

    @property
    def file(self):
        if len(self.parents) > 0:
            return self.parents[-1][1].location.file

    @property
    def lines(self):
        if len(self.parents) > 0:
            return (self.parents[-1][1].extent.start.line,
                    self.parents[-1][1].extent.start.column,
                    self.parents[-1][1].extent.end.line,
                    self.parents[-1][1].extent.end.column)

is_template_class = 0

def search_item_with(cursor: clang.cindex.Cursor, name):
    type = cursor.type
    cursor_type_spelling = type.spelling
    cursor_spelling = cursor.spelling
    if cursor_spelling == name:
        print(f'Found {name} item, repr(type): {repr(type)}')
        print(f'Found {name} item, cursor_type_spelling: {cursor_type_spelling}')
        print(f'Found {name} item, cursor_spelling: {cursor_spelling}')
        print(f'Found {name} item, repr(cursor): {repr(cursor)}')
        print(f'Found {name} item, str(cursor): {str(cursor)}')
        print(f'Found {name} item, dir(cursor): {dir(cursor)}')
        return True
    elif hasattr(cursor, 'get_children'):
        for child in cursor.get_children():
            is_found = search_item_with(child, name)
            if is_found:
                print('>>>>>>>>>>>>>>>>')
                print(f'Found in {name} item, repr(type): {repr(type)}')
                print(f'Found in {name} item, cursor_type_spelling: {cursor_type_spelling}')
                print(f'Found in {name} item, cursor_spelling: {cursor_spelling}')
                print(f'Found in {name} item, repr(cursor): {repr(cursor)}')
                print(f'Found in {name} item, str(cursor): {str(cursor)}')
                print(f'Found in {name} item, dir(cursor): {dir(cursor)}')
                print('<<<<<<<<<<<<<<<<')
                return True
    return False


def get_all_classes(cursor: clang.cindex.Cursor):
    """
    Find all references to the type named 'typename'
    :param cursor: clang.cindex.Cursor
    :return: None
    """
    found_classes = set()

    if cursor.kind == CursorKind.CLASS_DECL or cursor.kind == CursorKind.CLASS_TEMPLATE:
        if cursor.spelling == 'A':
            print('Found class A')
        class_decl = ClassDecl(cursor)
        if class_decl in found_classes:
            found_classes.remove(class_decl)
        found_classes.add(class_decl)

    if hasattr(cursor, 'get_children'):
        for child in cursor.get_children():
            for cl in get_all_classes(child):
                if cl in found_classes:
                    found_classes.remove(cl)
                found_classes.add(cl)

    return found_classes


def get_base_classes(cursor):
    bases = []
    if hasattr(cursor, 'get_children'):
        for child in cursor.get_children():
            if child.kind == clang.cindex.CursorKind.CXX_BASE_SPECIFIER:
                bases.append(child)
    return bases


def get_field_decls(cursor):
    field_decls = []
    if hasattr(cursor, 'get_children'):
        for child in cursor.get_children():
            if child.kind == clang.cindex.CursorKind.FIELD_DECL:
                field_decls.append(child)
    return field_decls


def filter_class_for_file(classes, base_path):
    print(f'base_path {base_path}')
    filter_classes = []
    for cl in classes:
        file_path = os.path.abspath(str(cl.class_decl.location.file))
        common_directory = os.path.commonpath([base_path, file_path])
        print(f'file_path {file_path}')
        print(f'common_directory {common_directory}')
        if base_path in common_directory:
            print(f'Filtered {file_path}')
            filter_classes.append(cl)
    return filter_classes


def group_by_file(classes: List[ClassDecl]):
    group_classes: Dict = dict()
    for cl in classes:
        file_path = str(cl.class_decl.location.file)
        if file_path not in group_classes:
            group_classes[file_path] = list()
        group_classes[file_path].append(cl)
    return group_classes


def group_by_lines(classes: List[ClassDecl]):
    group_classes: Dict = dict()
    for cl in classes:
        lines = cl.lines
        if lines not in group_classes:
            group_classes[lines] = list()
        group_classes[lines].append(cl)
    return group_classes


def get_compile_file(args):
    is_next_file = False
    for arg in args:
        if arg == '-c':
            is_next_file = True
        elif is_next_file:
            return arg


def adjust_args(args):
    new_args = [arg for arg in args if arg]
    idx = 0
    should_remove = False
    while idx < len(new_args):
        if new_args[idx] == '-o' or new_args[idx] == '-c':
            del new_args[idx]
            should_remove = True
        elif should_remove:
            del new_args[idx]
        else:
            idx += 1
    return new_args


def substitute_generated_files(command, generated_file_per_real_file):
    indx = 0
    while indx < len(command):
        if command[indx] in generated_file_per_real_file:
            command[indx] = generated_file_per_real_file[command[indx]]
        indx += 1
    # for generated_file in generated_file_per_real_file.values():
    #     print(f'generated_file is {generated_file}')
    #     _, file_extension = os.path.splitext(generated_file)
    #     print(f'file_extension is {file_extension}')
    #     if file_extension == '.h' or file_extension == '.hpp':
    #         command.insert(1, '-include')
    #         command.insert(2, f'{generated_file}')


if __name__ == '__main__':
    # json_file = sys.argv[1]
    print(f'sys.argv = {sys.argv}')
    import subprocess

    command = ["clang++-9"]
    command.extend(sys.argv[1:])

    build_directory = os.getcwd()
    args = command[1:]
    cpp_file = get_compile_file(args)
    if cpp_file is None:
        print(f'command is {command}')
        exit(subprocess.call(command))

    print(f'build_directory is {build_directory}')
    print(f'args is {args}')
    print(f'cpp_file is {cpp_file}')

    index = clang.cindex.Index.create()

    args = adjust_args(args)
    print(f'adjust_args is {args}')

    tu = index.parse(cpp_file,
                     args=args,
                     options=0)
    print('Translation unit: {}'.format(tu.spelling))
    all_gc_ptrs = set()
    class_inherited_from = set()
    cached_class_used_gc_ptr = set()
    cached_class_used_class = dict()
    classes = get_all_classes(tu.cursor)
    classes = filter_class_for_file(classes, str(Path(build_directory).parent))
    grouped_by_file_classes = group_by_file(classes)

    generated_file_per_real_file = dict()
    for file, classes_per_file in grouped_by_file_classes.items():
        print(f'file={file}')
        print(f'len(classes)={len(classes)}')
        gc_ptr_locations_pre_class = dict()
        grouped_by_lines_classes = group_by_lines(classes_per_file)
        sorted_lines = list(sorted(grouped_by_lines_classes.keys(), key=lambda x: x[2]))
        print(f'sorted_lines is {sorted_lines}')
        new_lines = []
        with open(file, 'r') as f:
            lines = f.readlines()
            indx = 0
            line_iter = iter(sorted_lines)
            line = next(line_iter)
            line_offset = dict()
            while indx < len(lines):
                cur_line = lines[indx]
                if line and line[2] == indx + 1:
                    column_offset = 0
                    if line[2] in line_offset:
                        column_offset = line_offset[line[2]]

                    member_names = []
                    classes_per_line = grouped_by_lines_classes[line]
                    for cl in classes_per_line:
                        bases = get_base_classes(cl.class_decl)
                        fields = get_field_decls(cl.class_decl)

                        connect_lines = []
                        for base in bases:
                            spelling = base.spelling
                            record_type = re.search(r'(class)?\s?(?P<type_name>[_A-Za-z][_A-Za-z0-9]*)',
                                                    spelling)
                            if record_type:
                                spelling = record_type.group('type_name')
                            connect_lines.append(f"    memory::call_ConnectBaseToRoot<{spelling}>(this, rootPtr);\n")

                        for field in fields:
                            spelling = field.spelling
                            connect_lines.append(f"    memory::call_ConnectFieldToRoot<decltype({spelling})>({spelling}, rootPtr);\n")


                        disconnect_lines = []
                        for base in bases:
                            spelling = base.spelling
                            record_type = re.search(r'(class)?\s?(?P<type_name>[_A-Za-z][_A-Za-z0-9]*)',
                                                    spelling)
                            if record_type:
                                spelling = record_type.group('type_name')
                            disconnect_lines.append(f"    memory::call_DisconnectBaseFromRoot<{spelling}>(this, isRoot, rootPtr);\n")

                        for field in fields:
                            spelling = field.spelling
                            disconnect_lines.append(f"    memory::call_DisconnectFieldFromRoot<decltype({spelling})>({spelling}, isRoot, rootPtr);\n")

                        if len(connect_lines) > 0 or len(disconnect_lines) > 0:
                            new_lines.append("\n")
                            new_lines.append(" public:\n")
                            new_lines.append("  // GENERATED CODE FOR GC_PTR\n")
                            new_lines.append("  // BEGIN GC_PTR\n")
                            if len(connect_lines) > 0:
                                new_lines.append("  void connectToRoot(const void * rootPtr) const {\n")
                                for connect_line in connect_lines:
                                    new_lines.append(connect_line)
                                new_lines.append("  }\n")
                                new_lines.append("\n")
                            if len(disconnect_lines) > 0:
                                new_lines.append("  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {\n")
                                for disconnect_line in disconnect_lines:
                                    new_lines.append(disconnect_line)
                                new_lines.append("  }\n")
                            new_lines.append("  // END GC_PTR\n")
                            new_lines.append(cur_line[line[3] - 2 - column_offset:])
                            try:
                                line = next(line_iter)
                            except:
                                line = None
                else:
                    new_lines.append(cur_line)
                indx += 1

        common_directory = os.path.commonpath([build_directory, file])
        start_of_file_index = file.find(common_directory)
        second_part_of_file = file[start_of_file_index + len(common_directory):]
        generated_file = build_directory + second_part_of_file

        generated_file_per_real_file[file] = generated_file
        with open(generated_file, 'w') as f:
            f.writelines(new_lines)

    substitute_generated_files(command, generated_file_per_real_file)
    print(f'command is {command}')
    exit(subprocess.call(command))
