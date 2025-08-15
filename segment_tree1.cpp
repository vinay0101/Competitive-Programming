#include <iostream>
#include <vector>
#include <numeric>

/**
 * @class SegmentTree
 * @brief A data structure for efficient range queries and point updates.
 *
 * This implementation uses a vector to represent the binary tree structure.
 * It's designed for range sum queries, but can be adapted for other
 * associative operations like minimum, maximum, or product.
 */
class SegmentTree {
private:
    std::vector<int> tree; // The segment tree, stored as a vector
    std::vector<int> nums; // The original input array
    int n;                 // The size of the input array

    /**
     * @brief Recursively builds the segment tree.
     * @param node The index of the current node in the 'tree' vector.
     * @param start The starting index of the segment in the original array.
     * @param end The ending index of the segment in the original array.
     */
    void build(int node, int start, int end) {
        // Base case: If the segment is a single element (a leaf node)
        if (start == end) {
            tree[node] = nums[start];
            return;
        }

        // Calculate the midpoint of the current segment
        int mid = start + (end - start) / 2;
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;

        // Recursively build the left and right subtrees
        build(left_child, start, mid);
        build(right_child, mid + 1, end);

        // The value of the internal node is the sum of its children
        tree[node] = tree[left_child] + tree[right_child];
    }

    /**
     * @brief Recursively updates a value in the tree.
     * @param node The index of the current node in the 'tree' vector.
     * @param start The starting index of the current node's segment.
     * @param end The ending index of the current node's segment.
     * @param idx The index of the element to update in the original array.
     * @param val The new value for the element.
     */
    void update(int node, int start, int end, int idx, int val) {
        // Base case: We've reached the leaf node corresponding to the index
        if (start == end) {
            nums[idx] = val;
            tree[node] = val;
            return;
        }

        int mid = start + (end - start) / 2;
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;

        // If the index is in the left child's range, recurse there
        if (start <= idx && idx <= mid) {
            update(left_child, start, mid, idx, val);
        } else { // Otherwise, recurse in the right child's range
            update(right_child, mid + 1, end, idx, val);
        }

        // After recursion, update the current node's value
        tree[node] = tree[left_child] + tree[right_child];
    }

    /**
     * @brief Recursively queries a range for its sum.
     * @param node The index of the current node in the 'tree' vector.
     * @param start The starting index of the current node's segment.
     * @param end The ending index of the current node's segment.
     * @param l The left boundary of the query range.
     * @param r The right boundary of the query range.
     * @return The sum of the elements in the query range [l, r].
     */
    int query(int node, int start, int end, int l, int r) {
        // Case 1: The current node's segment is completely outside the query range
        if (r < start || end < l) {
            return 0; // Return 0 as it's the identity for sum
        }

        // Case 2: The current node's segment is completely inside the query range
        if (l <= start && end <= r) {
            return tree[node];
        }

        // Case 3: The current node's segment partially overlaps with the query range
        int mid = start + (end - start) / 2;
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;

        // Query the left and right children and return their sum
        int p1 = query(left_child, start, mid, l, r);
        int p2 = query(right_child, mid + 1, end, l, r);

        return p1 + p2;
    }

public:
    /**
     * @brief Constructor for the SegmentTree.
     * @param arr The input array to build the tree from.
     */
    SegmentTree(const std::vector<int>& arr) {
        nums = arr;
        n = nums.size();
        // The size of the tree vector needs to be at most 4*n
        // to accommodate all nodes in the complete binary tree.
        tree.resize(4 * n);
        if (n > 0) {
            build(0, 0, n - 1);
        }
    }

    /**
     * @brief Public interface for updating an element.
     * @param index The index in the original array to update.
     * @param val The new value.
     */
    void update(int index, int val) {
        if (index < 0 || index >= n) return;
        update(0, 0, n - 1, index, val);
    }

    /**
     * @brief Public interface for querying a range sum.
     * @param left The left boundary of the range.
     * @param right The right boundary of the range.
     * @return The sum of elements from index 'left' to 'right'.
     */
    int query(int left, int right) {
        if (left < 0 || right >= n || left > right) return 0;
        return query(0, 0, n - 1, left, right);
    }

    /**
     * @brief Prints the segment tree for debugging purposes.
     */
    void printTree() {
        for (int i = 0; i < tree.size(); ++i) {
            if (tree[i] != 0) { // Print non-empty nodes
                std::cout << "tree[" << i << "] = " << tree[i] << std::endl;
            }
        }
    }
};

// --- Main function to demonstrate the SegmentTree ---
int main() {
    std::vector<int> nums = {1, 3, 5, 7, 9, 11};
    
    std::cout << "Original Array: ";
    for(int num : nums) std::cout << num << " ";
    std::cout << "\n\n";

    // Create a SegmentTree instance
    SegmentTree st(nums);
    
    std::cout << "Segment Tree constructed.\n";
    // st.printTree(); // Uncomment to see the internal tree structure
    std::cout << "\n";

    // --- Perform Queries ---
    std::cout << "--- Queries ---\n";
    // Query sum of range [1, 3] (3 + 5 + 7)
    std::cout << "Sum of range [1, 3]: " << st.query(1, 3) << std::endl; // Expected: 15

    // Query sum of range [0, 5] (full array)
    std::cout << "Sum of range [0, 5]: " << st.query(0, 5) << std::endl; // Expected: 36
    
    // Query sum of a single element at index 4
    std::cout << "Sum of range [4, 4]: " << st.query(4, 4) << std::endl; // Expected: 9
    std::cout << "\n";

    // --- Perform Updates ---
    std::cout << "--- Updates ---\n";
    // Update element at index 2 from 5 to 6
    std::cout << "Updating index 2 from 5 to 6...\n";
    st.update(2, 6);

    std::cout << "Array is now implicitly: 1 3 6 7 9 11\n\n";

    // --- Query again after update ---
    std::cout << "--- Queries After Update ---\n";
    // Query the same range [1, 3] again (3 + 6 + 7)
    std::cout << "Sum of range [1, 3]: " << st.query(1, 3) << std::endl; // Expected: 16

    // Query the full array again
    std::cout << "Sum of range [0, 5]: " << st.query(0, 5) << std::endl; // Expected: 37

    return 0;
}
