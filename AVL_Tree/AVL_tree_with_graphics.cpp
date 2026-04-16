#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
# define WIDTH 800
# define HEIGHT 600

typedef struct AVL_Node
{
    struct AVL_Node *left, *right;
    int data, bf;
}AVL;

AVL *tree = NULL;
AVL *disBalance = NULL;

void insert(AVL *, char);  // newnode, flag_to_print_insertion_message
int height(AVL *);
void add_bf(AVL *);  // tree
void findDisBalanceNode(AVL *, int);  // tree, item
void right_of_right_of_A(AVL *, AVL *);  // disBalance, parentNode    [left-rotation]
void left_of_left_of_A(AVL *, AVL *);  // disBalance,  parentNode     [right-rotation]
void right_of_left_of_A(AVL *, AVL *);  // disBalance, parentNode
void left_of_right_of_A(AVL *, AVL *);  // disBalance, parentNode
AVL* findParent(AVL *, AVL *);  // tree, node_to_find_parent
int select_rotation(AVL *, int);  // disBbalance, item
void display(AVL *);
void deleteNode(int); // item
AVL* search(int, AVL**);  // item, parrent_of_item_node
void postOrderly_insert_each_node(AVL*);  // subtree whichs each node we want to insert in main tree
int graphical_display(AVL *, int, int, int [][HEIGHT]);

int main()
{
    int ch, item;
	AVL *newnode, *ptr, *p_ptr;
	
    do {
    	printf("\n============================\n");
	    printf(" AVL TREE MENU\n");
	    printf("============================\n");
	    printf("1. Insert\n2. Delete\n3. Display\n4. Graphical Display\n5. Exit\n");
	    printf("============================\n");
	    
        printf("\n\tYour choice: ");
        scanf("%d", &ch);

        switch(ch)
        {
            case 1: 
			    
			    newnode = (AVL *)malloc(sizeof(AVL));
			    if(!newnode) {
			        // memory allocation failed
			        printf("\n[!] OVERFLOW: Memory allocation failed.\n");
			        continue ;
			    }
			    
			    printf("\tEnter the item to insert: ");
			    scanf("%d", &item);
			    
			    newnode->data = item;
			    newnode->left = NULL;
			    newnode->right = NULL;
			    
				insert(newnode, '1');
				break;
            case 3: 
                printf("\nInorder Traversal of AVL Tree:\n------------------------------\n");
                display(tree);
                printf("\n------------------------------\n");
                break;
            case 4:
				initwindow(WIDTH, HEIGHT, "My BGI window");
            	int occupancy[WIDTH][HEIGHT];
           		graphical_display(tree, 400, 10, occupancy);
//				getch();
				puts("Press any key to close the graph");
				getche();
           		closegraph();
            	break;
            case 5: 
                printf("\nExiting...\n");
                exit(1);
            case 2:
            	printf("Enter the item you want to delete :");
            	scanf("%d",&item);
            	deleteNode(item);
            	break;
            default: 
                printf("\n[!] You pressed a wrong key. Try again!\n");
        }
    }while(1);
}

void insert(AVL *newnode, char flag)
{
    AVL *ptr, *p_ptr;
    if(!tree) {
        // inserting first node of the tree
        tree = newnode;
        printf("\n\t[+] Item %d inserted successfully.\n", newnode->data);
        return ;
    }
    ptr = p_ptr = tree;
    while(ptr)
    {
        p_ptr = ptr;
        if(ptr->data > newnode->data)  { ptr = ptr->left; }
        else  { ptr = ptr->right; }
    }
    if(p_ptr->data > newnode->data)  { p_ptr->left = newnode; }
    else  { p_ptr->right = newnode; }
    /* node insertion completed */

    add_bf(tree);
    findDisBalanceNode(tree, newnode->data);
    
    if(disBalance)
    {
        // disBalance found
        AVL *p_disB = findParent(tree, disBalance);
        int check_rotation = select_rotation(disBalance, newnode->data);
        if(check_rotation == 1) {
            right_of_right_of_A(disBalance, p_disB);
        }
        else if(check_rotation == 2) {
            left_of_left_of_A(disBalance, p_disB);
        }
        else if(check_rotation == 3) {
            right_of_left_of_A(disBalance, p_disB);
        }
        else if(check_rotation == 4) {
            left_of_right_of_A(disBalance, p_disB);
        }

        disBalance = NULL;  // after rotation completed, there are no disbalance node
    }
    add_bf(tree);  // update balance factor after rotation
    
    
    /*this flag is set only for this purpose to handel delete message particularly*/
    if(flag)
    printf("\n\t[+] item %d inserted successfully.\n", newnode->data);
}

int height(AVL *root)
{
    if(!root) return 0;
    int h_left = height(root->left);
    int h_right = height(root->right);
    return (h_left > h_right ? h_left : h_right) + 1;
}

void add_bf(AVL *root)
{
    if(!root) return ;
    int bf;
    
    bf = height(root->left) - height(root->right);  // calculating bf
    
    root->bf = bf; // assign balance factor in each node
    
    add_bf(root->left);
    add_bf(root->right);
    return ;
}

void findDisBalanceNode(AVL *root, int item)
{
    AVL *ptr = root, *p_disB = ptr, *parent_disB = NULL;
    while(ptr != NULL)
    {
        if(!(-1 <= ptr->bf && ptr->bf <= 1)) {
            parent_disB = p_disB;
            disBalance = ptr;
        }
        p_disB = ptr;
        if(item < ptr->data)
        ptr = ptr->left;
        else
        ptr = ptr->right;
    }
    // return parent_disB;  // it can return NULL
}

AVL* findParent(AVL *root, AVL *node)
{
    AVL *ptr = root, *p_ptr = ptr;
    if(node == root) return root;
    while(ptr != NULL)
    {
        p_ptr = ptr;
        if(node->data > ptr->data)
        ptr = ptr->right;
        else
        ptr = ptr->left;
        if(ptr == node)
        return p_ptr;
    }
    return NULL;
}

void right_of_right_of_A(AVL *disBal, AVL *parentOfDisBal)
{
    AVL *d_branch;
    if(disBal == tree) {
        tree = disBal->right;
    } else {
        if(parentOfDisBal->left == disBal)
            parentOfDisBal->left = disBal->right;
        else
            parentOfDisBal->right = disBal->right;
    }
    d_branch = disBal->right->left;
    disBal->right->left = disBal;
    disBal->right = d_branch;
}
void left_of_left_of_A(AVL *disBal, AVL *parentOfDisBal)
{
    AVL *d_branch;
    if(disBal == tree) {
        tree = disBal->left;
    } else {
        if(parentOfDisBal->left == disBal)
            parentOfDisBal->left = disBal->left;
        else
            parentOfDisBal->right = disBal->left;
    }
    d_branch = disBal->left->right;
    disBal->left->right = disBal;
    disBal->left = d_branch;
}

void right_of_left_of_A(AVL *disBal, AVL *parentOfDisBal)
{
    AVL *parentOfDisBalArrowLeft = disBal;
    right_of_right_of_A(disBal->left, parentOfDisBalArrowLeft);
    left_of_left_of_A(disBal, parentOfDisBal);
}

void left_of_right_of_A(AVL *disBal, AVL *parentOfDisBal)
{
    AVL *parentOfDisBalArrowRight = disBal;
    left_of_left_of_A(disBal->right, parentOfDisBalArrowRight);
    right_of_right_of_A(disBal, parentOfDisBal);
}

int select_rotation(AVL *disB, int item)
{
    AVL *ptr = disB;
    int bf = ptr->bf;
    if(bf > 1) {
        ptr = ptr->left;
        if(item > ptr->data) return 3;  // r-l-A
        else return 2;  // l-l-A
    }
    else if(bf < -1) {
        ptr = ptr->right;
        if(item < ptr->data) return 4;  // l-r-A
        else return 1;  // r-r-A
    }
    return 0;  // no rotation needed
}


void display(AVL *ptr)
{
    //inorder traversal
    if(ptr == NULL) return;
    
    display(ptr->left);
    printf("%d\t",ptr->data);
    display(ptr->right);
    return;
}

void deleteNode(int item)
{
	AVL *targetNode, *p_targetNode, *temp, *freeNode;
	
	targetNode = search(item, &p_targetNode);
	/*
	if targetNode = tree, p_targetNode = tree
	if targetNode = anyNode, p_targetNode = parent_of_anyNode
	if targetNode = NotFound(NULL), p_targetNode = NULL
	*/
	
	if(targetNode == NULL) {  // not found
		printf("\t[!] item %d NOT found\n",item);
		return;
	}
	
	if(targetNode == tree) {  // root node
		freeNode = tree;
		temp = tree->left;
		tree = tree->right;
		free(freeNode); freeNode = NULL;  // free the occupied memory
		
		if(tree) {  // tree != NULL
			add_bf(tree);
		}
		else {  // tree == NULL
			tree = temp;
			if(tree) {
				add_bf(tree);
			}
			printf("\t[-] item %d deleted successfully.\n", item);
			return;
		}
		
		if(temp) {
			postOrderly_insert_each_node(temp);
			printf("\t[-] item %d deleted successfully.\n", item);
			return;
		}
	}
	else {  // target node is not root node
		freeNode = targetNode;
		if(targetNode->data < p_targetNode->data) {
			p_targetNode->left = targetNode->right;
		}else{
			p_targetNode->right = targetNode->right;
		}
		temp = targetNode->left;
		free(freeNode); freeNode = NULL;
		
		add_bf(tree);
		
		postOrderly_insert_each_node(temp);
		printf("\t[-] item %d deleted successfully.\n", item);
		return;
	}
}

void postOrderly_insert_each_node(AVL *root)
{
	if(root == NULL) return;
	
	postOrderly_insert_each_node(root->left);
	postOrderly_insert_each_node(root->right);
	
	root->right = root->left = NULL;
	root->bf = 0;
	insert(root, '\0');
}

AVL* search(int item, AVL** parentNode) {
    AVL* current = tree;
    *parentNode = NULL;

    while (current != NULL) {
        if (item == current->data) {
            // Item found
            if (*parentNode == NULL) {
                // Item is in root node, parentNode = root
                *parentNode = tree;
            }
            return current;
        }
        else if (item < current->data) {
            *parentNode = current;
            current = current->left;
        }
        else {
            *parentNode = current;
            current = current->right;
        }
    }

    // Item not found
    *parentNode = NULL;
    return NULL;
}

int graphical_display(AVL *ptr, int x, int y, int occupancy[][HEIGHT])
{
    //preorder traversal
    if(ptr == NULL) return x;
    
    int x1, x2;
    char str[10];
    sprintf(str, "%d", ptr->data);		//  sprintf(str, "%d", int_a) convert integer to string and store it in str
    
    if(ptr->left == NULL && ptr->right == NULL) {
    	if(occupancy[x][y] != 0) {
    		x = x + 100;
		}
		outtextxy(x, y, str);
		occupancy[x][y] = 1;
    	ellipse(x+6, y+6, 0, 0, 25, 15);
        return x;
    }
    
    x1 = graphical_display(ptr->left, x-50, y+50, occupancy);
    x2 = graphical_display(ptr->right, x+50, y+50, occupancy);
    
    int x_mid, y_mid, y_mid_50px_up;
	x_mid = (x1 + x2)/2;	
	y_mid = ((y+50+6) + (y+50+6))/2;
	y_mid_50px_up = y_mid - 50;

	if(ptr->left) {
		line(x1+6, y+50-10, x_mid, y_mid_50px_up+15);
	}
	if(ptr->right) {
		line(x2+6, y+50-10, x_mid, y_mid_50px_up+15);
	}
	
    outtextxy(x_mid - 6, y_mid_50px_up - 6, str);
    occupancy[x_mid][y_mid_50px_up] = 1;
    ellipse(x_mid, y_mid_50px_up, 0, 0, 25, 15);
    return x_mid-6;
}