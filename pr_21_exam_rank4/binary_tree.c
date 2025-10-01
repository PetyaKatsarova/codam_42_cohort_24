typedef struct s_node
{
    int           value;
    struct s_node *left;
    struct s_node *right;
}   t_node;

t_node *create_node(int value)
{
    t_node *new = malloc(sizeof(t_node));
    if (!new)
        return (NULL);
    new->value = value;
    new->left = NULL;
    new->right = NULL;
    return (new);
}
t_node *insert_bst(t_node *root, int value)
{
    if (root == NULL)
        return (create_node(value));
    
    if (value < root->value)
        root->left = insert_bst(root->left, value);
    else if (value > root->value)
        root->right = insert_bst(root->right, value);
    
    return (root);
}

//In-Order (Left, Root, Right) - Sorted for BST
void inorder(t_node *root)
{
    if (root == NULL)
        return;
    
    inorder(root->left);
    printf("%d ", root->value);
    inorder(root->right);
}

t_node *search_bst(t_node *root, int value)
{
    if (root == NULL || root->value == value)
        return (root);
    
    if (value < root->value)
        return (search_bst(root->left, value));
    
    return (search_bst(root->right, value));
}

int count_nodes(t_node *root)
{
    if (root == NULL)
        return (0);
    
    return (1 + count_nodes(root->left) + count_nodes(root->right));
}

int tree_height(t_node *root)
{
    if (root == NULL)
        return (0);
    
    int left_height = tree_height(root->left);
    int right_height = tree_height(root->right);
    
    if (left_height > right_height)
        return (left_height + 1);
    return (right_height + 1);
}

t_node *find_min(t_node *root)
{
    if (root == NULL)
        return (NULL);
    
    while (root->left != NULL)
        root = root->left;
    
    return (root);
}

// TODO: LEARN:
t_node *delete_node(t_node *root, int value)
{
    if (root == NULL)
        return (NULL);
    
    // Find the node to delete
    if (value < root->value)
        root->left = delete_node(root->left, value);
    else if (value > root->value)
        root->right = delete_node(root->right, value);
    else
    {
        // Node with only one child or no child
        if (root->left == NULL)
        {
            t_node *temp = root->right;
            free(root);
            return (temp);
        }
        else if (root->right == NULL)
        {
            t_node *temp = root->left;
            free(root);
            return (temp);
        }
        
        // Node with two children: get inorder successor
        t_node *temp = find_min(root->right);
        root->value = temp->value;
        root->right = delete_node(root->right, temp->value);
    }
    return (root);
}

// IF TREE IS BST binary search tree