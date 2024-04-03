#include "graf.h"
#include <stdio.h>
#include <stdlib.h>

node_t *init_node(short x, short y) {
  node_t *n = malloc(sizeof(node_t));
  n->count = 0;
  n->x = x;
  n->y = y;
  printf("Tworze node na (%d,%d)\n",x,y);
  return n;
}

void increase(node_t *node) {
  if (node->count == 0) {
    node->links = malloc(sizeof(node_t *));
  } else {
    node->links = realloc(node->links, sizeof(node_t *) * (node->count + 1));
  }
  node->count++;
}

void link_nodes(node_t* n1, node_t* n2){
  increase(n1);
  increase(n2);
  n1->links[n1->count - 1 ] = n2;
  n2->links[n2->count - 1 ] = n1;
  printf("Linkuje n1(%d,%d) i n2(%d,%d)\n",n1->x,n1->y,n2->x,n2->y);
}
