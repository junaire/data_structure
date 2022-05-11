#include <cassert>
#include <concepts>
#include <functional>
#include <iostream>
#include <vector>

enum class VisitKind {
  Pre,
  In,
  Post,
};

// Every tree nodes only hold the pointer to their children (could be nullptr)
// That said they have no ownship to their children, but just observers.
// The actual storage is in a continugous heap, in our case is std::vector.
template <typename NodeTy>
requires std::totally_ordered<NodeTy> class BinaryTree {
  struct TreeNode {
    explicit TreeNode(NodeTy &&Val) : Value(std::move(Val)) {}
    TreeNode *Lhs{nullptr};
    TreeNode *Rhs{nullptr};
    NodeTy Value;
  };

  TreeNode *Root{nullptr};

  std::vector<TreeNode> Nodes;

 public:
  BinaryTree() { Root = &Nodes.front(); };

  TreeNode &getRoot() { return *Root; }

  std::vector<TreeNode> &getUnderlyingData() { return Nodes; }

  std::size_t getNodeNum() const { return Nodes.size(); }

  void insertNode(NodeTy Val) { insertNodeImpl(Root, std::move(Val)); }

  TreeNode *searchNode(NodeTy Val) {
    return searchNodeImpl(Root, std::move(Val));
  }

  template <VisitKind VK, typename Visitor>
  void visitTree(Visitor visitor) {
    visitTreeImpl<VK>(Root, visitor);
  }

  void dump() { dumpImpl(0, Root); }

 private:
  TreeNode *createNode(NodeTy Val) {
    Nodes.emplace_back(std::move(Val));
    return &Nodes.back();
  }

  void insertNodeImpl(TreeNode *Node, NodeTy Val) {
    if (Node == nullptr && Nodes.empty()) {
      Root = createNode(std::move(Val));
      return;
    }

    if (Val < Node->Value) {
      if (Node->Lhs == nullptr)
        Node->Lhs = createNode(std::move(Val));
      else
        insertNodeImpl(Node->Lhs, std::move(Val));
    } else if (Val > Node->Value) {
      if (Node->Rhs == nullptr)
        Node->Rhs = createNode(std::move(Val));
      else
        insertNodeImpl(Node->Rhs, std::move(Val));
    } else
      assert(false && "Insert Nodes with same value is not allowed!");
  }

  TreeNode *searchNodeImpl(TreeNode *Node, NodeTy Val) {
    if (!Node) return nullptr;

    if (Val == Node->Value) return Node;

    if (Val < Node->Value)
      return searchNodeImpl(Node->Lhs, std::move(Val));
    else if (Val > Node->Value)
      return searchNodeImpl(Node->Rhs, std::move(Val));

    assert(false && "Search Error!");
  }

  template <VisitKind VK, typename Visitor>
  void visitTreeImpl(TreeNode *Node, Visitor visitor) {
    if (Node) {
      if constexpr (VK == VisitKind::Pre) visitor(Node);
      visitTreeImpl<VK>(Node->Lhs, visitor);
      if constexpr (VK == VisitKind::In) visitor(Node);
      visitTreeImpl<VK>(Node->Rhs, visitor);
      if constexpr (VK == VisitKind::Post) visitor(Node);
    }
  }

  void dumpImpl(int indent, TreeNode *Node) {
    if (!Node) return;

    printIndent(indent);
    std::cout << Node->Value << "\n";
    dumpImpl(indent + 2, Node->Lhs);
    dumpImpl(indent + 2, Node->Rhs);
  }

  void printIndent(int indent) {
    for (int i = 0; i < indent; i++) std::cout << " ";
  }
};
