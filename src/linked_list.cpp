#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
    Node* n = new Node(value, nullptr);
    if (size_ == 0) {
      front_ = n;
    } else {
      (*back_).next = n;
    }
    back_ = n;
    size_++;
  }

  bool LinkedList::Insert(int index, int value) {
    if (index > size_ || index < 0) {
      return false;
    }
    Node* n = new Node(value);
    if (size_ == 0) {
      front_ = n;
      back_ = n;
    } else if (index == 0) {
      (*n).next = front_;
      front_ = n;
    } else if (index == size_) {
      (*back_).next = n;
      back_ = n;
    } else {
      (*n).next = (*FindNode(index - 1)).next;
      (*FindNode(index - 1)).next = n;
    }
    size_++;
    return true;
  }

  bool LinkedList::Set(int index, int new_value) {
    if(index < 0 || index >= size_) {
      return false;
    }
    (*FindNode(index)).value = new_value;
    return true;
  }

  std::optional<int> LinkedList::Remove(int index) {
    if(index < 0 || index >= size_) {
      return std::nullopt;
    }
    int v;
    if(index == 0){
      v = (*front_).value;
      front_ = (*front_).next;
    } else {
      v = (*FindNode(index)).value;
      (*FindNode((index - 1))).next = (*FindNode(index)).next;
    }
    size_--;
    return v;
  }

  void LinkedList::Clear() {
    size_ = 0;
    front_ = nullptr;
    back_ = nullptr;
  }

  std::optional<int> LinkedList::Get(int index) const {
    if(index < 0 || index >= size_) {
      return std::nullopt;
    }
    Node* n = FindNode(index);
    return (*n).value;
  }

  std::optional<int> LinkedList::IndexOf(int value) const {
    Node* n = front_;
    for(int i = 0; i < size_; i++){
      if((*n).value == value){
        return i;
      }
      n= (*n).next;
    }
    return std::nullopt;
  }

  bool LinkedList::Contains(int value) const {
    Node* n = front_;
    for(int i = 0; i < size_; i++){
      if((*n).value == value){
        return true;
      }
      n = (*n).next;
    }
    return false;
  }

  bool LinkedList::IsEmpty() const {
    return size_ == 0;
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {
    if(front_ == nullptr) {
      return std::nullopt;
    }
    return (*front_).value;
  }

  std::optional<int> LinkedList::back() const {
    if(back_ == nullptr) {
      return std::nullopt;
    }
    return (*back_).value;
  }

  Node* LinkedList::FindNode(int index) const {
    if(index >= size_ || index < 0) {
      return nullptr;
    }
    Node* n = front_;
    for(int i = 0; i < index; i++){
      n = (*n).next;
    }
    return n;
  }

  // ?????? ????????????????????????
  LinkedList::LinkedList(const std::vector<int>& values) {

    if (values.empty()) {
      return;
    }

    auto* curr_node = new Node(values.front());
    front_ = curr_node;

    for (int index = 1; index < values.size() - 1; ++index) {
      curr_node->next = new Node(values[index]);
      curr_node = curr_node->next;
    }

    if (values.size() == 1) {
      back_ = front_;
    } else {
      curr_node->next = new Node(values.back());
      back_ = curr_node->next;
    }

    size_ = static_cast<int>(values.size());
  }

  std::vector<int> LinkedList::toVector() const {

    if (front_ == nullptr || size_ == 0) {
      return {};
    }

    std::vector<int> array;
    array.reserve(size_);

    for (auto* node = front_; node != nullptr; node = node->next) {
      array.push_back(node->value);
    }

    return array;
  }

}  // namespace assignment