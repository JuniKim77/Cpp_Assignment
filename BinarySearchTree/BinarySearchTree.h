#pragma once

#include <memory>
#include <vector>

namespace BinarySearch
{
	template<typename T>
	class TreeNode;

	template<typename T>
	class BinarySearchTree final
	{
	public:
		void Insert(std::unique_ptr<T> data);
		bool Search(const T& data);
		bool Delete(const T& data);
		const std::weak_ptr<TreeNode<T>> GetRootNode() const;

		static std::vector<T> TraverseInOrder(const std::shared_ptr<TreeNode<T>> startNode);

	protected:
		void InsertHelper(std::shared_ptr<TreeNode<T>> root, std::unique_ptr<T> data);
		std::shared_ptr<TreeNode<T>> SearchHelper(const std::shared_ptr<TreeNode<T>> root, const T& data);
		std::shared_ptr<TreeNode<T>> DeleteHelper(std::shared_ptr<TreeNode<T>> root);
		static void TraverseInOrderHelper(const std::shared_ptr<TreeNode<T>> root, std::vector<T>& v);
	private:
		std::shared_ptr<TreeNode<T>> mTree;
	};

	template<typename T>
	void BinarySearchTree<T>::Insert(std::unique_ptr<T> data)
	{
		if (mTree == nullptr)
		{
			mTree = std::make_shared<TreeNode<T>>(std::move(data));
		}
		else
		{
			InsertHelper(mTree, std::move(data));
		}

	}

	template<typename T>
	inline void BinarySearchTree<T>::InsertHelper(std::shared_ptr<TreeNode<T>> root, std::unique_ptr<T> data)
	{
		if (*root->Data >= *data)
		{
			if (root->Left == nullptr)
			{
				root->Left = std::make_shared<TreeNode<T>>(root, std::move(data));
			}
			else
			{
				InsertHelper(root->Left, std::move(data));
			}
		}
		else
		{
			if (root->Right == nullptr)
			{
				root->Right = std::make_shared<TreeNode<T>>(root, std::move(data));
			}
			else
			{
				InsertHelper(root->Right, std::move(data));
			}
		}
	}

	template<typename T>
	const std::weak_ptr<TreeNode<T>> BinarySearchTree<T>::GetRootNode() const
	{
		std::weak_ptr<TreeNode<T>> root = mTree;
		return root;
	}

	template<typename T>
	bool BinarySearchTree<T>::Search(const T& data)
	{
		std::shared_ptr<TreeNode<T>> result = SearchHelper(mTree, data);
		if (result == nullptr)
		{
			return false;
		}
		else
		{
			return true;
		}

	}

	template<typename T>
	inline std::shared_ptr<TreeNode<T>> BinarySearchTree<T>::SearchHelper(const std::shared_ptr<TreeNode<T>> root, const T& data)
	{
		if (root == nullptr || *root->Data == data)
		{
			return root;
		}
		if (*root->Data > data)
		{
			return SearchHelper(root->Left, data);
		}
		else
		{
			return SearchHelper(root->Right, data);
		}
	}

	template<typename T>
	bool BinarySearchTree<T>::Delete(const T& data)
	{
		std::shared_ptr<TreeNode<T>> result = SearchHelper(mTree, data);
		if (result == nullptr)
		{
			return false;
		}
		else
		{
			std::weak_ptr<TreeNode<T>> temp = result->Parent;
			// case1 : Head Node == no parent
			if (temp.expired())
			{
				mTree = DeleteHelper(result);
			}
			else
			{
				std::shared_ptr<TreeNode<T>> parent = temp.lock();
				if (*parent->Data < data)
				{
					parent->Right = DeleteHelper(result);
					if (parent->Right != nullptr)
					{
						parent->Right->Parent = parent;
					}
				}
				else
				{
					parent->Left = DeleteHelper(result);
					if (parent->Left != nullptr)
					{
						parent->Left->Parent = parent;
					}
				}
			}
			return true;
		}
	}

	template<typename T>
	inline std::shared_ptr<TreeNode<T>> BinarySearchTree<T>::DeleteHelper(std::shared_ptr<TreeNode<T>> root)
	{
		// case1 : no child
		if (root->Left == nullptr && root->Right == nullptr)
		{
			//root = nullptr;
			return nullptr;
		}
		// case2-1 : right child only
		else if (root->Left == nullptr && root->Right != nullptr)
		{
			return root->Right;
		}
		// case2-2 : left child only
		else if (root->Left != nullptr && root->Right == nullptr)
		{
			return root->Left;
		}
		// case3 : both child
		else
		{
			std::shared_ptr<TreeNode<T>> parent;
			std::shared_ptr<TreeNode<T>> replacement = root->Right;
			while (replacement->Left != nullptr)
			{
				parent = replacement;
				replacement = replacement->Left;
			}
			replacement->Left = root->Left;
			root->Left->Parent = replacement;
			if (root->Right != replacement)
			{
				if (replacement->Right == nullptr)
				{
					parent->Left = nullptr;
				}
				else
				{
					parent->Left = replacement->Right;
					replacement->Right->Parent = parent;
				}
				replacement->Right = parent;
				parent->Parent = replacement;
			}
			return replacement;
		}
	}

	template<typename T>
	inline void BinarySearchTree<T>::TraverseInOrderHelper(const std::shared_ptr<TreeNode<T>> root, std::vector<T>& v)
	{
		if (root == nullptr)
		{
			return;
		}
		TraverseInOrderHelper(root->Left, v);
		v.push_back(*root->Data);
		TraverseInOrderHelper(root->Right, v);
	}

	template<typename T>
	std::vector<T> BinarySearchTree<T>::TraverseInOrder(const std::shared_ptr<TreeNode<T>> startNode)
	{
		std::vector<T> v;
		TraverseInOrderHelper(startNode, v);
		return v;
	}
}