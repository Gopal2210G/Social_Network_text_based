#ifndef SOCIAL_H
#define SOCIAL_H

// This header file defines the data structures for a social network simulation.

// this is  a network where 4 type of nodes individuals, groups, businesses, and
// organizations each have inherit properties from nodes and also have some
// additional properties.

// This code defines structures for each node type, along with structures for
// links and content (posts). It also tracks the number of nodes of each type in
// the network.

// Define a maximum number of links for each node
#define Max_links 50

// Forward declarations for structs to avoid circular dependencies
struct Node;
struct Individual;
struct Business;

// Forward declarations for structs to avoid circular dependencies
int num_individuals = 0;
int num_groups = 0;
int num_businesses = 0;
int num_organisations = 0;

// Define a struct to represent a link between nodes
typedef struct Link {
  int target_id;
  struct Individual *target_node; // Pointer to the target node
} Link;

// Define a struct to represent content (posts)

typedef struct Content {
  char content[1000];
} Content;

// Define a struct to represent a generic node
typedef struct Node {
  int id;
  char name[50];
  char date[20];
  int n_link;
  char type;
  int active; // Flag indicating if the node is active
  Link link[Max_links];
  Content post[100];
} Node;

// A struct to represent an individual node (inherits from Node)
typedef struct Individual {
  Node base;
  char birthday[20];
} Individual;

typedef struct Business {
  Node base;
  int location_x;
  int location_y;
  Individual *owner;         // Pointer to the owner of the business
  Individual *customer[100]; // Array of customers of the business
} Business;

typedef struct Group {
  Node base;
  Individual *mem[100];
  Business *add[20]; // Array of businesses that are members of the group
} Group;

typedef struct Organisation {
  Node base;
  int location_x;
  int location_y;
  Individual *mem[100];
} Organisation;

#endif
