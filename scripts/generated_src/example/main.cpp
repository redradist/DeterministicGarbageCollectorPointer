#include <gc_ptr.hpp>
#include <iostream>
#include <atomic>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <mutex>
#include <algorithm>
#include "some_lib.hpp"

class A;

template <typename T, typename Base>
class Df : public Base {
 public:
  T t2t;

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    memory::call_ConnectBaseToRoot<Base>(this, rootPtr);
    memory::call_ConnectFieldToRoot<decltype(t2t)>(t2t, rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    memory::call_DisconnectBaseFromRoot<Base>(this, isRoot, rootPtr);
    memory::call_DisconnectFieldFromRoot<decltype(t2t)>(t2t, isRoot, rootPtr);
  }
  // END GC_PTR
};

class DD {
 public:
  A *a0;

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    memory::call_ConnectFieldToRoot<decltype(a0)>(a0, rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    memory::call_DisconnectFieldFromRoot<decltype(a0)>(a0, isRoot, rootPtr);
  }
  // END GC_PTR
};

class C {
 public:
  C() {
    std::cout << "C()" << std::endl;
  }

  ~C() {
    std::cout << "~C()" << std::endl;
  }

  std::string getName() {
    return "class A";
  }

  A * a0;
  memory::gc_ptr<A> a0_ptr_;
  memory::gc_ptr<A> a1_ptr_;
  std::vector<int> array;

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    a0_ptr_.connectToRoot(rootPtr);
    a1_ptr_.connectToRoot(rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    a0_ptr_.disconnectFromRoot(isRoot, rootPtr);
    a1_ptr_.disconnectFromRoot(isRoot, rootPtr);
  }
  // END GC_PTR

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    a0_ptr_.connectToRoot(rootPtr);
    a1_ptr_.connectToRoot(rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    a0_ptr_.disconnectFromRoot(isRoot, rootPtr);
    a1_ptr_.disconnectFromRoot(isRoot, rootPtr);
  }
  // END GC_PTR

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    a0_ptr_.connectToRoot(rootPtr);
    a1_ptr_.connectToRoot(rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    a0_ptr_.disconnectFromRoot(isRoot, rootPtr);
    a1_ptr_.disconnectFromRoot(isRoot, rootPtr);
  }
  // END GC_PTR

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    a0_ptr_.connectToRoot(rootPtr);
    a1_ptr_.connectToRoot(rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    a0_ptr_.disconnectFromRoot(isRoot, rootPtr);
    a1_ptr_.disconnectFromRoot(isRoot, rootPtr);
  }
  // END GC_PTR

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    a1_ptr_.connectToRoot(rootPtr);
    a0_ptr_.connectToRoot(rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    a1_ptr_.disconnectFromRoot(isRoot, rootPtr);
    a0_ptr_.disconnectFromRoot(isRoot, rootPtr);
  }
  // END GC_PTR

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    memory::call_ConnectFieldToRoot<decltype(a0)>(a0, rootPtr);
    memory::call_ConnectFieldToRoot<decltype(a0_ptr_)>(a0_ptr_, rootPtr);
    memory::call_ConnectFieldToRoot<decltype(a1_ptr_)>(a1_ptr_, rootPtr);
    memory::call_ConnectFieldToRoot<decltype(array)>(array, rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    memory::call_DisconnectFieldFromRoot<decltype(a0)>(a0, isRoot, rootPtr);
    memory::call_DisconnectFieldFromRoot<decltype(a0_ptr_)>(a0_ptr_, isRoot, rootPtr);
    memory::call_DisconnectFieldFromRoot<decltype(a1_ptr_)>(a1_ptr_, isRoot, rootPtr);
    memory::call_DisconnectFieldFromRoot<decltype(array)>(array, isRoot, rootPtr);
  }
  // END GC_PTR
}; class Dfs {
  A * a0;

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    memory::call_ConnectFieldToRoot<decltype(a0)>(a0, rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    memory::call_DisconnectFieldFromRoot<decltype(a0)>(a0, isRoot, rootPtr);
  }
  // END GC_PTR
};

class B {
 public:
  B() {
    std::cout << "B()" << std::endl;
    c_ptr_ = memory::gc_ptr<C>{new C()};
    c_ptr_.create_object();
  }

  ~B() {
    std::cout << "~B()" << std::endl;
  }

  std::string getName() {
    return "class A";
  }

  memory::gc_ptr<C> c_ptr_;
  std::vector<int> array;

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    c_ptr_.connectToRoot(rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    c_ptr_.disconnectFromRoot(isRoot, rootPtr);
  }
  // END GC_PTR

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    c_ptr_.connectToRoot(rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    c_ptr_.disconnectFromRoot(isRoot, rootPtr);
  }
  // END GC_PTR

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    c_ptr_.connectToRoot(rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    c_ptr_.disconnectFromRoot(isRoot, rootPtr);
  }
  // END GC_PTR

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    c_ptr_.connectToRoot(rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    c_ptr_.disconnectFromRoot(isRoot, rootPtr);
  }
  // END GC_PTR

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    c_ptr_.connectToRoot(rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    c_ptr_.disconnectFromRoot(isRoot, rootPtr);
  }
  // END GC_PTR

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    memory::call_ConnectFieldToRoot<decltype(c_ptr_)>(c_ptr_, rootPtr);
    memory::call_ConnectFieldToRoot<decltype(array)>(array, rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    memory::call_DisconnectFieldFromRoot<decltype(c_ptr_)>(c_ptr_, isRoot, rootPtr);
    memory::call_DisconnectFieldFromRoot<decltype(array)>(array, isRoot, rootPtr);
  }
  // END GC_PTR
};

class A {
 public:
  A() {
    std::cout << "A()" << std::endl;
    b_ptr_.create_object();
  }

  ~A() {
    std::cout << "~A()" << std::endl;
  }

  std::string getName() {
    return "class A";
  }

  memory::gc_ptr<B> b_ptr_;

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    b_ptr_.connectToRoot(rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    b_ptr_.disconnectFromRoot(isRoot, rootPtr);
  }
  // END GC_PTR

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    b_ptr_.connectToRoot(rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    b_ptr_.disconnectFromRoot(isRoot, rootPtr);
  }
  // END GC_PTR

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    b_ptr_.connectToRoot(rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    b_ptr_.disconnectFromRoot(isRoot, rootPtr);
  }
  // END GC_PTR

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    b_ptr_.connectToRoot(rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    b_ptr_.disconnectFromRoot(isRoot, rootPtr);
  }
  // END GC_PTR

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    b_ptr_.connectToRoot(rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    b_ptr_.disconnectFromRoot(isRoot, rootPtr);
  }
  // END GC_PTR

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    memory::call_ConnectFieldToRoot<decltype(b_ptr_)>(b_ptr_, rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    memory::call_DisconnectFieldFromRoot<decltype(b_ptr_)>(b_ptr_, isRoot, rootPtr);
  }
  // END GC_PTR
};

class D {
 public:
  Df<A, A> fd;
  const A a0;
  A const *a1;

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    a0.connectToRoot(rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    a0.disconnectFromRoot(isRoot, rootPtr);
  }
  // END GC_PTR

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    a0.connectToRoot(rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    a0.disconnectFromRoot(isRoot, rootPtr);
  }
  // END GC_PTR

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    a0.connectToRoot(rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    a0.disconnectFromRoot(isRoot, rootPtr);
  }
  // END GC_PTR

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    a0.connectToRoot(rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    a0.disconnectFromRoot(isRoot, rootPtr);
  }
  // END GC_PTR

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    a0.connectToRoot(rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    a0.disconnectFromRoot(isRoot, rootPtr);
  }
  // END GC_PTR

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    memory::call_ConnectFieldToRoot<decltype(fd)>(fd, rootPtr);
    memory::call_ConnectFieldToRoot<decltype(a0)>(a0, rootPtr);
    memory::call_ConnectFieldToRoot<decltype(a1)>(a1, rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    memory::call_DisconnectFieldFromRoot<decltype(fd)>(fd, isRoot, rootPtr);
    memory::call_DisconnectFieldFromRoot<decltype(a0)>(a0, isRoot, rootPtr);
    memory::call_DisconnectFieldFromRoot<decltype(a1)>(a1, isRoot, rootPtr);
  }
  // END GC_PTR
};

namespace asdasd {
class CC : public A {

 private:
  memory::gc_ptr<B> b_ptr_;

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    A::connectToRoot(rootPtr);
    b_ptr_.connectToRoot(rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    A::disconnectFromRoot(isRoot, rootPtr);
    b_ptr_.disconnectFromRoot(isRoot, rootPtr);
  }
  // END GC_PTR

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    A::connectToRoot(rootPtr);
    b_ptr_.connectToRoot(rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    A::disconnectFromRoot(isRoot, rootPtr);
    b_ptr_.disconnectFromRoot(isRoot, rootPtr);
  }
  // END GC_PTR

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    A::connectToRoot(rootPtr);
    b_ptr_.connectToRoot(rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    A::disconnectFromRoot(isRoot, rootPtr);
    b_ptr_.disconnectFromRoot(isRoot, rootPtr);
  }
  // END GC_PTR

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    A::connectToRoot(rootPtr);
    b_ptr_.connectToRoot(rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    A::disconnectFromRoot(isRoot, rootPtr);
    b_ptr_.disconnectFromRoot(isRoot, rootPtr);
  }
  // END GC_PTR

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    A::connectToRoot(rootPtr);
    b_ptr_.connectToRoot(rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    A::disconnectFromRoot(isRoot, rootPtr);
    b_ptr_.disconnectFromRoot(isRoot, rootPtr);
  }
  // END GC_PTR

 public:
  // GENERATED CODE FOR GC_PTR
  // BEGIN GC_PTR
  void connectToRoot(const void * rootPtr) const {
    memory::call_ConnectBaseToRoot<A>(this, rootPtr);
    memory::call_ConnectFieldToRoot<decltype(b_ptr_)>(b_ptr_, rootPtr);
  }

  void disconnectFromRoot(const bool isRoot, const void * rootPtr) const {
    memory::call_DisconnectBaseFromRoot<A>(this, isRoot, rootPtr);
    memory::call_DisconnectFieldFromRoot<decltype(b_ptr_)>(b_ptr_, isRoot, rootPtr);
  }
  // END GC_PTR
};
}


int main() {
  std::cout << "" << CD{}.getFile() << std::endl;

  // NOTE(redra): Test 0
  std::thread thr;
  {
    memory::gc_ptr<A> a0_ptr_{new A()};
    a0_ptr_->b_ptr_->c_ptr_->a1_ptr_ = a0_ptr_;

    memory::gc_ptr<A> a_copy_ptr_{};
    a_copy_ptr_.create_object();
    a_copy_ptr_ = a0_ptr_;

    thr = std::thread {[a0_ptr_]() {
      std::this_thread::sleep_for(std::chrono::seconds(2));
      std::cout << "Object name is " << a0_ptr_->getName() << std::endl;
    }};
    memory::gc_ptr<A> a1_ptr_{};
    a1_ptr_.create_object();
    a1_ptr_->b_ptr_ = a0_ptr_->b_ptr_;
    a1_ptr_->b_ptr_->c_ptr_->a0_ptr_  = a1_ptr_;
  }

  thr.join();


  // NOTE(redra): Test 1
//  Df<A, A> ad;
//  std::thread thr;
//  {
//    memory::gc_ptr<A> a0_ptr_{new A()};
//    a0_ptr_->b_ptr_->c_ptr_->a1_ptr_ = a0_ptr_;
//
//    ad.t2t.b_ptr_ = a0_ptr_->b_ptr_;
//    memory::gc_ptr<A> a_copy_ptr_{};
//    a_copy_ptr_.create_object();
//    a_copy_ptr_ = a0_ptr_;
//
//    asdasd::CC cc;
//    auto c0_ptr_ = a0_ptr_->b_ptr_->c_ptr_;
//    thr = std::thread {[a0_ptr_]() {
//      std::this_thread::sleep_for(std::chrono::seconds(2));
//      std::cout << "Object name is " << a0_ptr_->getName() << std::endl;
//      std::this_thread::sleep_for(std::chrono::seconds(2));
//      a0_ptr_->b_ptr_->c_ptr_ = new C();
//      std::cout << "Object name is " << a0_ptr_->getName() << std::endl;
//    }};
//    memory::gc_ptr<A> a1_ptr_{};
//    a1_ptr_.create_object();
//    a1_ptr_->b_ptr_ = a0_ptr_->b_ptr_;
//    a1_ptr_->b_ptr_->c_ptr_->a0_ptr_  = a1_ptr_;
//  }
//  thr.join();

  // NOTE(redra): Test 2
//  memory::gc_ptr<A> a0_ptr_{new A()};
//  memory::gc_ptr<A> a1_ptr_ = a0_ptr_;
  return 0;
}