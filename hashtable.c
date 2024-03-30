
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char *key;
	void *value;
	struct node *next;
} node_t;

typedef node_t **hash_table_t;

#define MAX_SIZE 64;

hash_table_t hashtable() {
	hash_table_t table = (node_t **)calloc(64, sizeof(node_t));

	return table;
}

// get the length of key to generate hash. Uses the `modulus` function with
// MAX_SIZE.
int hash(const char *key) {
	const int length = strlen(key);
	const int hash_value = length % MAX_SIZE;
	return hash_value;
}

// find the node of the searching key by traversing through the linkedlist.
node_t *find_node(node_t *head, const char *key) {
	node_t *current = head;
	while (current != NULL) {
		// string compare the key and return from the loop with current node.
		int key_found = strcmp(key, current->key);
        if (key_found == 0)
            return current;
        else 
            break;
		current = current->next;
	}
	// if the key is not found inside the linkedlist return NULL.
	return NULL;
}

void append_node(node_t *head, node_t *node) {
	node_t *current = head;
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = node;
}

void add(hash_table_t *hash_table, const char *key, const void *value) {
	const int hash_value = hash(key);
	// find the address of the head node in the array.
	node_t *head = *hash_table[hash_value];
	// create the new node and add the value, copy the key string instead of arg
	// pointer.
	node_t *node = (node_t *)malloc(sizeof(node_t));
	char *key_copy = malloc(strlen(key) + 1);
	strcpy(key_copy, key);
	node->key = key_copy;
	void *value_copy = malloc(sizeof(value));
	memcpy(value_copy, value, sizeof(value));
	node->value = value_copy;
	node->next = NULL;
	// check if the head node is NULL if not,
	// iterate through linkedlist and add the node, if head node does not exist
	// create new node and add the value to the node
	if (head == NULL)
		head = node;
	else
		append_node(head, node);

	return;
}

void *get(hash_table_t *hash_table, const char *key) {
	const int hash_value = hash(key);
	// find the address of the head node in the array
	node_t *head = *hash_table[hash_value];
	// iterate through linkedlist and return the value inside the node
	const node_t *node = find_node(head, key);
	if (node != NULL)
		return node->value;
	return NULL;
}

int main() {
	hash_table_t table = hashtable();
	// add value to the hashtable
	add(&table, "name", "sam");
	add(&table, "age", "28");
	void *val = get(&table, "name");
	printf("name is %s", (char *)val);
	return 0;
}
