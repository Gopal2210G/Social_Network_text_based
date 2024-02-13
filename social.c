// Add social.h file in this code which have structures of main code

#include "social.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int next_id = 1;

// Function to generate unique id
int generate_unique_id() { return next_id++; }

// Declare arrays to store pointers to individuals, groups, businesses, and organisations
Individual **individuals = NULL;
Group **groups = NULL;
Business **businesses = NULL;
Organisation **organisations = NULL;

// Function to check if a string is a subsequence of another string
int isSubsequence(const char *str, const char *subseq) {

  int strLen = strlen(str);
  int subseqLen = strlen(subseq);
  int i = 0, j = 0;

  while (i < strLen && j < subseqLen) {
    if (str[i] == subseq[j]) {
      j++;
    }
    i++;
  }

  return (j == subseqLen);
}

// Function to search for content posted by any node

void search_content(char *search_con) {
  int i;
  for (i = 0; i < num_individuals; i++) {
    if (isSubsequence(individuals[i]->base.post->content, search_con) == 1) {
      printf("Individual ID %d: %s\n", individuals[i]->base.id,
             individuals[i]->base.post->content);
      return;
    }
  }
  for (i = 0; i < num_businesses; i++) {
    if (isSubsequence(businesses[i]->base.post->content, search_con) == 1) {
      printf("Business ID %d: %s\n", businesses[i]->base.id,
             businesses[i]->base.post->content);
      return;
    }
  }
  for (i = 0; i < num_organisations; i++) {
    if (isSubsequence(organisations[i]->base.post->content, search_con) == 1) {
      printf("Organisation ID %d: %s\n", organisations[i]->base.id,
             organisations[i]->base.post->content);
      return;
    }
  }
  for (i = 0; i < num_groups; i++) {
    if (isSubsequence(groups[i]->base.post->content, search_con) == 1) {
      printf("Group ID %d: %s\n", groups[i]->base.id,
             groups[i]->base.post->content);
      return;
    }
  }
  printf("No results found.\n");
}

// Function to process user commands
void processCommand(char *command) {
  if (strcasecmp(command, "print all nodes") == 0) {
    for (int i = 1; i <= num_individuals; i++) {
      printf("%d. id=%d   type=%c  Name=%s  Birthday=%s  No. of "
             "Connections: %d\n",
             i, individuals[i - 1]->base.id, individuals[i - 1]->base.type,
             individuals[i - 1]->base.name, individuals[i - 1]->birthday,
             individuals[i - 1]->base.n_link);
    };
    for (int i = 1; i <= num_businesses; i++) {
      printf("%d. id=%d   type=%c  Name=%s  No. of "
             "Connections: %d\n",
             i, businesses[i - 1]->base.id, businesses[i - 1]->base.type,
             businesses[i - 1]->base.name, businesses[i - 1]->base.n_link);
    };
    for (int i = 1; i <= num_organisations; i++) {
      printf("%d. id=%d   type=%c  Name=%s  No. of "
             "Connections: %d\n",
             i, organisations[i - 1]->base.id, organisations[i - 1]->base.type,
             organisations[i - 1]->base.name,
             organisations[i - 1]->base.n_link);
    }
    for (int i = 1; i <= num_groups; i++) {
      printf("%d. id=%d   type=%c  Name=%s  No. of "
             "Connections: %d\n",
             i, groups[i - 1]->base.id, groups[i - 1]->base.type,
             groups[i - 1]->base.name, groups[i - 1]->base.n_link);
    }
  }
}

// Function to search for a node by name and date of birth
Node *search_node_by_name_and_dob(const char *target_name,
                                  const char *target_dob, int type) {
  if (type == 1) {
    for (int i = 0; i < num_individuals; i++) {
      if (strcmp(individuals[i]->birthday, target_dob) == 0 &&
          strcasecmp(individuals[i]->base.name, target_name) == 0) {
        return (Node *)individuals[i];
      }
    }

    return NULL;
  } else if (type == 3) {
    for (int i = 0; i < num_groups; i++) {
      if (strcasecmp(groups[i]->base.name, target_name) == 0) {
        return (Node *)groups[i];
      }
    }
    return NULL;
  } else if (type == 2) {
    for (int i = 0; i < num_businesses; i++) {
      if (strcasecmp(businesses[i]->base.name, target_name) == 0) {
        return (Node *)businesses[i];
      }
    }
    return NULL;
  } else if (type == 4) {
    for (int i = 0; i < num_organisations; i++) {
      if (strcasecmp(organisations[i]->base.name, target_name) == 0) {
        return (Node *)organisations[i];
      }
    }
    return NULL;
  }
  return NULL;
}

// Function to print information about a node
void printNode(Node *node) {
  if (node != NULL && node->active == 1) {
    printf("Type: %c\n", node->type);
    printf("Node ID: %d\n", node->id);
    printf("Node Name: %s\n", node->name);
    printf("Creation Date: %s\n", node->date);
  } else {
    printf("Error: Node is NULL\n");
  }
  printf("\n");
}

// Function to print one-hop linked nodes for a given node
void printOneHopLinkedNodes(Node *node) {
  if (node != NULL && node->active == 1) {
    printf("1-hop linked nodes for %s:\n", node->name);
    for (int i = 0; i < node->n_link; ++i) {
      if (node->link[i].target_node != NULL) {
        printf("- Node ID: %d\n", node->link[i].target_node->base.id);
        printf("  Node Type: %c\n", node->link[i].target_node->base.type);
        printf("  Node Name: %s\n", node->link[i].target_node->base.name);
        printf("  Creation Date: %s\n", node->link[i].target_node->base.date);
      } else {
        printf("- Error: Target node is NULL\n");
      }
    }
  } else {
    printf("Error: Input node is NULL\n");
  }
}

Individual *find_node(int target_id) {
  for (int i = 0; i < num_individuals; i++) {
    if (individuals[i]->base.id == target_id) {
      return individuals[i];
    }
  }
  return NULL;
}

Business *find_nodeB(int target_id) {
  for (int i = 0; i < num_businesses; i++) {
    if (businesses[i]->base.id == target_id) {
      return businesses[i];
    }
  }
  return NULL;
}

Group *find_nodeG(int target_id) {
  for (int i = 0; i < num_groups; i++) {
    if (groups[i]->base.id == target_id) {
      return groups[i];
    }
  }
  return NULL;
}

Organisation *find_nodeO(int target_id) {
  for (int i = 0; i < num_organisations; i++) {
    if (organisations[i]->base.id == target_id) {
      return organisations[i];
    }
  }
  return NULL;
}

void search_content_of_individual_in_Group(Individual *source) {
  printf("All content posted by individuals linked to a given %s:\n",
         source->base.name);
  Group *temp = find_nodeG(source->base.id);
  int cnt = 0;
  for (int i = 0; i < source->base.n_link; i++) {
    if (find_nodeG(source->base.link[i].target_id) == temp) {
      cnt++;
      Individual *target = find_node(source->base.link[i].target_id);
      printf("%d.ID=%d, Name=%s\n", cnt, target->base.id, target->base.name);
      printf("Post: %s\n", target->base.post->content);
    }
  }
}

// Function to search and display content posted by individuals linked to a
// given individual in an organization
void search_content_of_individual_in_Oraganisation(Individual *source) {
  Organisation *temp = find_nodeO(source->base.id);
  int cnt = 0;
  for (int i = 0; i < source->base.n_link; i++) {
    if (find_nodeO(source->base.link[i].target_id) == temp) {
      cnt++;
      Individual *target = find_node(source->base.link[i].target_id);
      printf("%d.ID=%d, Name=%s\n", cnt, target->base.id, target->base.name);
      printf("Post: %s\n", target->base.post->content);
    }
  }
}

// Function to search and display content posted by individuals linked to a
// given individual in a group
Group *create_group(char *name, char *date) {
  Group *group = malloc(sizeof(Group));
  if (group) {
    group->base.id = generate_unique_id();
    printf("Unique ID of Group is: %d\n", group->base.id);
    strcpy(group->base.name, name);
    strcpy(group->base.date, date);
    group->base.n_link = 0;
    group->base.active = 1;
    group->base.type = 'G';
    printf("Are you want add Member in your Group: ");
    char ch;
    getchar();
    scanf("%c", &ch);
    int i_id;
    if (ch == 'y') {
      printf("Enter the IDs of Member (0 for stop):\n");
      scanf("%d", &i_id);
    }
    while (i_id != 0) {
      Individual *target_node;
      target_node = find_node(i_id);
      if (target_node) {
        printf("Member added\n");
      } else {
        printf("Not exist individual\n");
      }
      printf("Enter the IDs of Member:\n");
      scanf("%d", &i_id);
    }

    printf("Are you want add buisness in your Group: ");
    char ch2;
    getchar();
    scanf("%c", &ch2);
    if (ch == 'y') {
      int i_id2;
      printf("Enter the IDs of buisness:\n");
      scanf("%d", &i_id2);
      while (i_id2 != 0) {
        Individual *target_node;
        target_node = find_node(i_id);
        if (target_node) {
          printf("buisness added\n");
        } else {
          printf("Not exist buisness\n");
        }
        printf("Enter the IDs of buisness:\n");
        scanf("%d", &i_id2);
      }
    }
  }
  return group;
}

// Function to create a new business
Business *create_business(char *name, char *date, int location_x,
                          int location_y) {
  Business *business = malloc(sizeof(Business));
  if (business) {
    business->base.id = generate_unique_id();
    printf("Unique ID of this Business: %d\n", business->base.id);
    strcpy(business->base.name, name);
    strcpy(business->base.date, date);
    business->base.n_link = 0;
    business->base.type = 'B';
    business->location_x = location_x;
    business->location_y = location_y;
    business->base.active = 1;
    printf("Enter Owner id:\t");
    int owner_id;
    scanf("%d", &owner_id);
    Individual *target_node = find_node(owner_id);
    if (target_node) {
      printf("Owner added\n");
      business->owner = target_node;
    } else {
      printf("Not exist individual\n");
    }
    printf("Are you want add Customers in your buisness:('y'/'n') ");
    char ch;
    getchar();
    scanf("%c", &ch);
    int i_id;
    if (ch == 'y') {
      printf("Enter the IDs of Customers (0 for stop):\n");
      scanf("%d", &i_id);
    }
    while (i_id != 0) {
      Individual *target_node;
      target_node = find_node(i_id);
      if (target_node) {
        printf("Member added\n");
      } else {
        printf("Not exist individual\n");
      }
      printf("Enter the IDs of Customers (0 for stop):\n");
      scanf("%d", &i_id);
    }
  }
  return business;
}

// Function to create a new organization
Organisation *create_organisation(char *name, char *date, int location_x,
                                  int location_y) {
  Organisation *organisation = malloc(sizeof(Organisation));
  if (organisation) {
    organisation->base.id = generate_unique_id();
    printf("Unique ID: of this organisation %d\n", organisation->base.id);
    organisation->base.type = 'O';
    strcpy(organisation->base.name, name);
    strcpy(organisation->base.date, date);
    organisation->base.n_link = 0;
    organisation->base.active = 1;
    organisation->location_x = location_x;
    organisation->location_y = location_y;

    printf("Are you want add Member in your organisation: ");
    char ch;
    getchar();
    scanf("%c", &ch);
    int i_id;
    if (ch == 'y') {
      printf("Enter the IDs of Member (0 for stop):\n");
      scanf("%d", &i_id);
    }
    while (i_id != 0) {
      Individual *target_node;
      target_node = find_node(i_id);
      if (target_node) {
        printf("Member added\n");
      } else {
        printf("Not exist individual\n");
      }
      printf("Enter the IDs of Member:\n");
      scanf("%d", &i_id);
    }
  }
  return organisation;
}

// Function to add a link between two individual nodes
void add_link(Individual *source, Individual *target) {

  if (source->base.n_link < Max_links) {
    source->base.link[source->base.n_link].target_id = target->base.id;
    source->base.link[source->base.n_link].target_node = target;
    source->base.n_link++;
  } else {
    printf("Error: Node has reached maximum link capacity.\n");
  }
}

// Function to link an individual node to other nodes
Individual *link_id(Individual *individual) {
  int target_id;
  do {
    printf("Enter the ID of the node to link to (0 to stop): ");
    scanf("%d", &target_id);
    Individual *target_node = find_node(target_id);
    if (target_node) {
      add_link(individual, target_node);
    } else {
      printf("Not exist individual\n");
    }
  } while (target_id != 0);
  return individual;
}

// Function to create a new individual node
Individual *create_individual(char *name, char *date, char *birthday) {
  Individual *individual = malloc(sizeof(Individual));
  if (individual) {
    individual->base.id = generate_unique_id();
    printf("Unique ID: %d\n", individual->base.id);
    strcpy(individual->base.name, name);
    strcpy(individual->base.date, date);
    strcpy(individual->birthday, birthday);
    individual->base.type = 'I';
    individual->base.active = 1;
    individual->base.n_link = 0;
    printf("Do you want to link this node to any existing nodes? (y/n): ");
    char choice;
    scanf(" %c", &choice);
    if (choice == 'y') {
      link_id(individual);
    }
  }
  return individual;
}

// Function to create a new node based on its type and reallocation of its size
Node *create_node(int type, char *name, char *date, char *dob, int location_x,
                  int location_y) {
  Node *node = NULL;

  switch (type) {
  case 1:
    node = (Node *)create_individual(name, date, dob);

    /*realloc_dynamic_array
      Resizes a dynamic array to accommodate the specified number of elements.*/
    if (node) {
      individuals =
          realloc(individuals, (num_individuals + 1) * sizeof(Individual *));
      individuals[num_individuals++] = (Individual *)node;
    }
    break;
  case 3:
    node = (Node *)create_group(name, date);
    if (node) {
      groups = realloc(groups, (num_groups + 1) * sizeof(Group *));
      groups[num_groups++] = (Group *)node;
    }
    break;
  case 2:
    node = (Node *)create_business(name, date, location_x, location_y);
    if (node) {
      businesses =
          realloc(businesses, (num_businesses + 1) * sizeof(Business *));
      businesses[num_businesses++] = (Business *)node;
    }
    break;
  case 4:
    node = (Node *)create_organisation(name, date, location_x, location_y);
    if (node) {
      organisations = realloc(organisations,
                              (num_organisations + 1) * sizeof(Organisation *));
      organisations[num_organisations++] = (Organisation *)node;
    }
    break;
  default:
    printf("Invalid node type.\n");
  }

  return node;
}

int main() {
  printf("--------SOCIAL NETWORK APPLICATION--------\n");
  while (1) {
    // Menu options
    printf("\n1.Create Account\n 2.Delete Account\n 3.Search\n 4.Print\n "
           "5.Post\n 6.Search Content\n 7.Display Content  posted by "
           "individuals linked to a given individual\n 8.Command\n");
    int n;
    scanf("%d", &n);
    switch (n) {
    case 1: {
      // Create Account
      printf("Select a type of Account:\n");
      printf("1.Individual\n 2.Business\n 3.Group\n 4.Organisation\n");
      int k;
      getchar();
      scanf("%d", &k);
      char date[12];

      printf("Enter Date in DD/MM/YYYY format:");
      getchar();
      scanf("%11[^\n]", date);

      if (k == 1) {
        // Create Individual Account
        char name[25];
        char dob[12];

        printf("Enter Name of Individual:\t");
        getchar();
        scanf("%24[^\n]", name);

        printf("Enter Date of Birth in DD/MM/YYYY format:");
        getchar();
        scanf("%11[^\n]", dob);

        create_node(k, name, date, dob, 0, 0);

      } else if (k == 2) {
        // Create Business Account
        char name[25];
        int x, y;
        printf("Enter Name of Business:\t");
        getchar();
        scanf(" %24[^\n]", name);
        printf("Enter the Location Coordinates(X & Y respectively) of "
               "Business:\t");
        scanf("%d %d", &x, &y);
        create_node(k, name, date, 0, x, y);
      } else if (k == 3) {
        // Create Group Account
        char name[25];
        printf("Enter Name of Group:\t");
        getchar();
        scanf("%24[^\n]", name);
        create_node(k, name, date, 0, 0, 0);
      } else if (k == 4) {
        // Create Organisation Account
        char name[25];
        printf("Enter Name of Organisation:\t");
        getchar();
        scanf("%24[^\n]", name);
        create_node(k, name, date, 0, 0, 0);
      } else {
        printf("Invalid option\n");
      }
      break;
    }

    case 2: {
      // Delete Account
      printf("Select our type of Account which you want to delete:\n");
      printf("1.Individual\n 2.Business\n 3.Group\n 4.Organisation\n");
      int k;
      scanf("%d", &k);
      if (k == 1) {
        // Delete Individual Account
        int id;
        printf("Enter the ID of Individual:\t");
        scanf("%d", &id);
        Individual *target_node = find_node(id);
        if (target_node) {
          for (int i = 0; i < num_individuals; i++) {
            if (individuals[i]->base.id == target_node->base.id) {
              individuals[i]->base.active = 0;
              free(individuals[i]);
              for (int j = i; j < num_individuals - 1; j++) {
                individuals[j] = individuals[j + 1];
              }
              num_individuals--;
              break;
            }
          }
        } else {
          printf("Not exist individual\n");
        }
      }
      if (k == 2) {
        // Delete Business Account
        int id;
        printf("Enter the ID of Business:\t");
        scanf("%d", &id);
        Business *target_node = find_nodeB(id);
        if (target_node) {
          for (int i = 0; i < num_businesses; i++) {
            if (businesses[i]->base.id == target_node->base.id) {
              businesses[i]->base.active = 0;
              free(businesses[i]);
              for (int j = i; j < num_businesses - 1; j++) {
                businesses[j] = businesses[j + 1];
              }
              num_businesses--;
              break;
            }
          }
        } else {
          printf("Not exist business\n");
        }
      }
      if (k == 3) {
        // Delete Group Account
        int id;
        printf("Enter the ID of Group:\t");
        scanf("%d", &id);
        Group *target_node = find_nodeG(id);
        if (target_node) {
          for (int i = 0; i < num_groups; i++) {
            if (groups[i]->base.id == target_node->base.id) {
              groups[i]->base.active = 0;
              free(groups[i]);
              for (int j = i; j < num_groups - 1; j++) {
                groups[j] = groups[j + 1];
              }
              num_groups--;
              break;
            }
          }
        } else {
          printf("Not exist group\n");
        }
      }
      if (k == 4) {
        // Delete Organisation Account
        int id;
        printf("Enter the ID of Organisation:\t");
        scanf("%d", &id);
        Organisation *target_node = find_nodeO(id);
        if (target_node) {
          for (int i = 0; i < num_organisations; i++) {
            if (organisations[i]->base.id == target_node->base.id) {
              organisations[i]->base.active = 0;
              free(organisations[i]);
              for (int j = i; j < num_organisations - 1; j++) {
                organisations[j] = organisations[j + 1];
              }
              num_organisations--;
              break;
            }
          }
        } else {
          printf("Not exist organisation\n");
        }
      }
      break;
    }
    case 3: {
      // Search Account
      printf("Select our type of Account which you want to search:\n");
      printf("1.Individual\n 2.Business\n 3.Group\n 4.Organisation\n");
      int k;
      scanf("%d", &k);
      printf("Enter the Name of Individual:\t");
      char name[25];
      getchar();
      scanf("%24[^\n]", name);
      if (k == 1) {
        // Search Individual Account
        char dob[12];
        printf("Enter the Date of Birth of Individual:\t");
        getchar();
        scanf("%11[^\n]", dob);
        Node *search_node = search_node_by_name_and_dob(name, dob, k);
        if (search_node) {
          printf("Node found:\n");
          printNode(search_node);
        } else {
          printf("Node not found.\n");
        }
      } else if (k == 2 || k == 3 || k == 4) {
        // Search Business, Group, or Organisation Account
        Node *search_node = search_node_by_name_and_dob(name, 0, k);
        if (search_node) {
          printf("Node found:\n");
          printf("Are you want Data of this node('y'/'n') \t");
          char choice;
          scanf("%c", &choice);
          if (choice == 'y') {
            printNode(search_node);
          }
        }
        // print_node(search_node);
        else {
          printf("Node not found.\n");
        }
      }
      break;
    }
    case 4: {
      // Print Account
      printf("1.Print all 1-hop linked nodes to a given input node\n "
             "2.Print_Node\n");
      int k;
      scanf(" %d", &k);
      if (k == 1) {
        // Print 1-hop linked nodes
        printf("Enter the id of node:\t");
        int id;
        scanf("%d", &id);
        Individual *target_node = find_node(id);
        if (target_node) {
          printOneHopLinkedNodes((Node *)target_node);
        } else {
          printf("Node not found\n");
        }
      } else if (k == 2) {
        // Print Node
        printf("Enter the id of node:\t");
        int id;
        scanf("%d", &id);
        Individual *target_node = find_node(id);
        Business *target_node2 = find_nodeB(id);
        Group *target_node3 = find_nodeG(id);
        Organisation *target_node4 = find_nodeO(id);
        if (target_node) {
          printNode((Node *)target_node);
        } else if (target_node2) {
          printNode((Node *)target_node2);
        } else if (target_node3) {
          printNode((Node *)target_node3);
        } else if (target_node4) {
          printNode((Node *)target_node4);
        }

      break;
    }
    }
    case 5: {
      // Post Content
      printf("Selet our type of Account which you want to use for post:\n");
      printf("1.Individual\n 2.Business\n 3.Group\n 4.Organisation\n");
      int k;
      scanf("%d", &k);
      if (k == 1) {
        // Post Content for Individual Account
        int id;
        printf("Enter the ID of Individual:\t");
        scanf("%d", &id);
        Individual *target_node = find_node(id);
        if (target_node) {
          printf("Enter the content of post:\t");
          getchar();
          scanf("%999[^\n]", target_node->base.post->content);
        }
      } else if (k == 2) {
        // Post Content for Business Account
        int id;
        printf("Enter the ID of Business:\t");
        scanf("%d", &id);
        Business *target_node = find_nodeB(id);
        if (target_node) {
          printf("Enter the content of post:\t");
          getchar();
          scanf("%999[^\n]", target_node->base.post->content);
        }
      } else if (k == 3) {
        // Post Content for Group Account
        int id;
        printf("Enter the ID of Group:\t");
        scanf("%d", &id);
        Group *target_node = find_nodeG(id);
        if (target_node) {
          printf("Enter the content of post:\t");
          getchar();
          scanf("%999[^\n]", target_node->base.post->content);
        }
      } else if (k == 4) {
        // Post Content for Organisation Account
        int id;
        printf("Enter the ID of Organisation:\t");
        scanf("%d", &id);
        Organisation *target_node = find_nodeO(id);
        if (target_node) {
          printf("Enter the content of post:\t");
          getchar();
          scanf("%999[^\n]", target_node->base.post->content);
        }
      }
      break;
    }

    case 6: {
      // Search Content
      char str[100];
      printf("Search Content:\n");
      getchar();
      scanf("%99[^\n]", str);
      search_content(str);
      break;
    }

    case 7: {
      // Display Content
      printf("All content posted by individuals linked to a given individual "
             "if they have a common group or organization.\n");
      printf("Enter the ID of Individual:\t");
      int id;
      scanf("%d", &id);
      Individual *target_node = find_node(id);
      if (target_node) {
        search_content_of_individual_in_Group(target_node);
        search_content_of_individual_in_Oraganisation(target_node);
      }
      break;
    }
    case 8: {
      char userInput[50];
      // Command
      printf("Enter a command (type 'Exit' to quit and 'print all nodes' to "
             "Print all Data): ");
      printf("Enter a command: ");
      getchar();
      scanf(" %49[^\n]", userInput);
      if (strcmp(userInput, "exit") == 0) {
        exit(0);
      } else {
        processCommand(userInput);
      }
      break;
    }
    default:
      break;
    }
  }
  }