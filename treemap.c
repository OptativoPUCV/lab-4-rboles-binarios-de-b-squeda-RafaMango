#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}
/*
Implemente la función createTreeMap en el archivo treemap.c. Esta función recibe la función de comparación de claves y crea un mapa (TreeMap)
inicializando sus variables. El siguiente código muestra como inicializar la función de comparación. Reserve memoria, inicialice el resto de
variables y retorne el mapa.
*/
TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2))
{
    TreeMap *map = (TreeMap*)malloc(sizeof(TreeMap));
    if(map == NULL)return NULL;
    map->root = NULL;
    map->current = NULL;
    map->lower_than = lower_than; //quizas sea mejor poner new en vez de map
    return map;
}

/*
Implemente la función void insertTreeMap(TreeMap * tree, void* key, void * value). Esta función inserta un nuevo dato (key,value) en el árbol
y hace que el current apunte al nuevo nodo. Para insertar un dato, primero debe realizar una búsqueda para encontrar donde debería ubicarse.
Luego crear el nuevo nodo y enlazarlo. Si la clave del dato ya existe retorne sin hacer nada (recuerde que el mapa no permite claves repetidas).
*/
void insertTreeMap(TreeMap * tree, void* key, void * value)
{
    TreeNode* actual = tree->root;
    TreeNode* padre = NULL;
    while(actual != NULL)
    {
        padre = actual;
        if(is_equal(tree, key, actual->pair->key))
        {
            return; //ya existe
        }
        else if(tree->lower_than(key, actual->pair->key))
        {
            actual = actual->left;
        }
        else
        {
            actual = actual->right;
        }
    }
    TreeNode* newNode = createTreeNode(key, value);
    newNode->parent= padre;
    if(padre == NULL){
        tree->root = newNode;
    }
    else if(tree->lower_than(key, padre->pair->key))
    {
        padre->left = newNode;

    }
    else
    {
        padre->right = newNode;
    }
    tree->current = newNode;
}

TreeNode * minimum(TreeNode * x)
{
    if(x == NULL)return NULL;
    while( x->left != NULL)
    {
        x = x->left;
    }
    return x;
}


/*
 Implemente la función void removeNode(TreeMap * tree, TreeNode* node). Esta función elimina el nodo node del árbol tree. Recuerde que para eliminar
 un node existen 3 casos: Nodo sin hijos: Se anula el puntero del padre que apuntaba al nodo Nodo con un hijo: El padre del nodo pasa a ser padre de
 su hijo Nodo con dos hijos: Descienda al hijo derecho y obtenga el menor nodo del subárbol (con la función minimum). Reemplace los datos (key,value)
 de node con los del nodo "minimum". Elimine el nodo minimum (para hacerlo puede usar la misma función removeNode).
*/
void removeNode(TreeMap * tree, TreeNode* node)
{
    if(node == NULL)return;

    //Caso 1
    if(node->left == NULL && node->right == NULL)
    {
        if(node->parent == NULL)
        {
            tree->root = NULL;
        }
        else if(node->parent->left == node)
        {
            node->parent->left = NULL;
        }
        else
        {
            node->parent->right = NULL;
        }
        free(node);
        return;
    }
    //caso 2
    if(node->left == NULL || node->right == NULL)
    {
        TreeNode* hijo;
        if(node->left != NULL)
            hijo = node->left;
        else
            hijo = node->right;
        if(node->parent == NULL)
        {
            tree->root = hijo;
        }
        else if(node->parent->left == node)
        {
            node->parent->left = hijo;
        }
        else
        {
            node->parent->right = hijo;
        }
        hijo->parent = node->parent;
        free(node);
        return;
    }
    //caso 3
    TreeNode* minNode = minimum(node->right);
    node->pair = minNode->pair;
    removeNode(tree, minNode);

}

void eraseTreeMap(TreeMap * tree, void* key)
{
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}


/*
Implemente la función Pair* searchTreeMap(TreeMap* tree, void* key), la cual busca el nodo con clave igual a key y retorna el Pair asociado
 al nodo. Si no se encuentra la clave retorna NULL. Recuerde hacer que el current apunte al nodo encontrado.
*/

Pair * searchTreeMap(TreeMap * tree, void* key)
{
    TreeNode* aux = tree->root;
    while(aux != NULL)
    {
        if(tree->lower_than(key, aux->pair->key)) //is_equal
        {
            aux = aux->left;
        }
        else if(tree->lower_than(aux->pair->key, key))
        {
            aux = aux->right;
        }
        else
        {
            tree->current = aux;
            return aux->pair;
        }
    }


    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key)
{
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree)
{
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree)
{
    return NULL;
}
