#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct {
struct Node*right;
struct Node*left;
char data[40];
}Node;

Node*newNode(char*word){
Node*n=malloc(sizeof(Node));
strcpy(n->data,word);
n->left=NULL;
n->right=NULL;
return n;
}
Node* BST_Constructor(Node*root,char* word){
if (root == NULL)
return newNode(word);
if (strcasecmp(word,root->data)<0)
root->left=BST_Constructor(root->left, word);
else if (strcasecmp(word,root->data)>0)
root->right = BST_Constructor(root->right, word);
return root;
}
int BST_Height(Node*root){
if(root==NULL)return 0;
return 1+ fmax(BST_Height(root->left),BST_Height(root->right));
}
Node* Dictionary_Loader(char*dictionary,Node*root){
int counter=0;
FILE*f1=fopen(dictionary,"r");
while(!feof(f1)){
char temp[40];
fscanf(f1,"%s",temp);
counter++;
root=BST_Constructor(root,temp);
}
fclose(f1);
printf("Dictionary Loaded Successfully...!");
printf("\n..................................");
printf("\nSize = %d",counter);
printf("\n..................................");
printf("\nHeight = %d",BST_Height(root)-1);
printf("\n..................................");
return root;
}
Node* findMax(Node* root)
{
    while (root->right) {
        root = root->right;
    }

    return root;
}
Node* Get_Predecessor(Node* root,Node*current)
{
Node* predecessor = NULL;
while (1)
{
if (strcasecmp(current->data,root->data)<0)   root = root->left;

else if (strcasecmp(current->data,root->data)>0)
  {
    predecessor = root;
    root = root->right;
  }
else {
    if (root->left!=NULL) {
    predecessor = findMax(root->left);
        }
    break;
        }

    }
    return predecessor;
}
Node* FindMin( Node* root) {
	if(root == NULL) return NULL;
	while(root->left != NULL)
		root = root->left;
	return root;
}

 Node* Get_Successor( Node* root,Node*current) {
  if(current == NULL) return NULL;
	if(current->right != NULL) {
		return FindMin(current->right);
	}
	else {
		Node* successor = NULL;
		 Node* parent = root;
		while(parent != current) {
			if(strcasecmp(current->data,parent->data)<0) {
				successor = parent;
				parent = parent->left;
			}
			else
				parent = parent->right;
		}
		return successor;
	}
}

void BST_Checker(char*word,Node*dictionary){
Node*pre=NULL;
Node*successor=NULL;
Node*current=dictionary;
Node*predcessor=NULL;
int flag=0;
while (current!=NULL)
{
if (strcasecmp(word,current->data)==0){
flag=1;pre=current;break;}
else if (strcasecmp(word,current->data)<0){
pre=current;
current=current->left;

}
else{
pre=current;
current = current->right;
}
}
if(flag!=1){
successor=Get_Successor(dictionary,pre);
predcessor=Get_Predecessor(dictionary,pre);
}
if(flag==1)printf("Correct");

else if(successor!=NULL&&predcessor!=NULL) printf("Incorrect, Suggestions :  %s %s %s ",pre->data,predcessor->data,successor->data);
else if(successor!=NULL) printf("Incorrect, Suggestions :  %s %s  ",pre->data,successor->data);
else if(predcessor!=NULL) printf("Incorrect, Suggestions :  %s  %s ",pre->data,predcessor->data);
else printf("Incorrect, Suggestions :  %s   ",pre->data);

}

void BST_Spelling_Check(char*sentence,Node*dictionary){
char*delimiter=" ";
char*token=malloc(40*sizeof(char));
token=strtok(sentence,delimiter);
printf("%s - ",token);
BST_Checker(token,dictionary);
while(token){
    token=strtok(NULL,delimiter);
    if(token==NULL)break;
   printf("\n%s - ",token);
   BST_Checker(token,dictionary);
}

}

void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}

int main()
{

FILE *f=fopen("EN-US-Dictionary.txt","r");
if(f!=NULL){

char expression[120]="";
Node*root=NULL;
root=Dictionary_Loader("EN-US-Dictionary.txt",root);
printf("\nEnter a sentence :\n");
fgets(expression, 119, stdin);
replaceNewLineBySpace(expression);
BST_Spelling_Check(expression,root);

    }
    else printf("Dictionary not loaded sucessfully");
    fclose(f);
    return 0;
}
