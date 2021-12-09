#pragma once
#include "Cube.h"


template<typename T>
struct TreeNode
{
    // All 12 children (initially nullptr), map to RotationType
    TreeNode<T>** children = nullptr;

    // Parent pointer
    TreeNode<T>* parent = nullptr;

    // Store data last (unknown size/alignment)
    T data = T();

    // Index/update children safely from here
    TreeNode<T>*& child(RotationType type) {
        // If no children added yet
        if (children == nullptr) children = new TreeNode<T>*[12] {nullptr};
        // otherwise index children
        return children[static_cast<size_t>(type)];
    }

    TreeNode(T obj) : data(obj) {}
    TreeNode(TreeNode<T>* parent, T obj) : parent(parent), data(obj) {}

    ~TreeNode() {
        if (children == nullptr) return;
        for (int i = 0; i < 12; ++i)
        {
            if (children[i] != nullptr) delete children[i];
        }
        delete children;
        children = nullptr;
    }
};