/** 
 * Copyright (c) 2014 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/map.h"

struct map_node_t {
  unsigned hash;
  void *value;
  map_node_t *next;
  map_node_t *oNext; // Doubly linked list pointers
};


static unsigned map_hash(const char *str) {
  unsigned hash = 5381;
  while (*str) {
    hash = ((hash << 5) + hash) ^ *str++;
  }
  return hash;
}


static map_node_t *map_newnode(const char *key, void *value, int vsize) {
  map_node_t *node;
  int ksize = strlen(key) + 1;
  int voffset = ksize + ((sizeof(void*) - ksize) % sizeof(void*));
  node = malloc(sizeof(*node) + voffset + vsize);
  if (!node) return NULL;
  memcpy(node + 1, key, ksize);
  node->hash = map_hash(key);
  node->value = ((char*) (node + 1)) + voffset;
  memcpy(node->value, value, vsize);
  node->oNext = NULL;
  return node;
}


static int map_bucketidx(map_base_t *m, unsigned hash) {
  return hash & (m->nbuckets - 1);
}


static void map_addnode(map_base_t *m, map_node_t *node) {
  int n = map_bucketidx(m, node->hash);
  node->next = m->buckets[n];
  m->buckets[n] = node;

  if (m->tail) {
    m->tail->oNext = node;
    m->tail = node;
  } else {
    m->head = m->tail = node;
  }
}



static int map_resize(map_base_t *m, int nbuckets) {
  map_node_t *node, *next, *head;
  map_node_t **buckets;
  head = m->head;

  buckets = realloc(m->buckets, sizeof(*m->buckets) * nbuckets);
  if (buckets != NULL) {
    m->buckets = buckets;
    m->nbuckets = nbuckets;
  }

  if (m->buckets) {
    memset(m->buckets, 0, sizeof(*m->buckets) * m->nbuckets);
    node = head;
    do {
      if(m->nnodes){
        next = node->oNext;
        map_addnode(m, node);
        node = next;
      }
    } while (node != m->head && node != NULL);
  }
  /* Return error code if realloc() failed */
  return (buckets == NULL) ? -1 : 0;
}

map_node_t* previous_node(map_base_t* map, map_node_t* node) {
    map_node_t* p = map->head;
    map_node_t* prev = NULL;
    while(p != NULL && p != node){
        prev = p;
        p = p->oNext;
    }
    return prev;
}


static map_node_t **map_getref(map_base_t *m, const char *key) {
  unsigned hash = map_hash(key);
  map_node_t **next;
  if (m->nbuckets > 0) {
    next = &m->buckets[map_bucketidx(m, hash)];
    while (*next) {
      if ((*next)->hash == hash && !strcmp((char*) (*next + 1), key)) {
        return next;
      }
      next = &(*next)->next;
    }
  }
  return NULL;
}


void map_deinit_(map_base_t *m) {
  map_node_t *next, *node;
  int i;
  i = m->nbuckets;
  while (i--) {
    node = m->buckets[i];
    while (node) {
      next = node->next;
      free(node);
      node = next;
    }
  }
  free(m->buckets);
}


void *map_get_(map_base_t *m, const char *key) {
  map_node_t **next = map_getref(m, key);
  return next ? (*next)->value : NULL;
}


int map_set_(map_base_t *m, const char *key, void *value, int vsize) {
  int n, err;
  map_node_t **next, *node;
  /* Find & replace existing node */
  next = map_getref(m, key);
  if (next) {
    memcpy((*next)->value, value, vsize);
    return 0;
  }
  /* Add new node */
  node = map_newnode(key, value, vsize);
  if (node == NULL) goto fail;
  if (m->nnodes >= m->nbuckets) {
    n = (m->nbuckets > 0) ? (m->nbuckets << 1) : 1;
    err = map_resize(m, n);
    if (err) goto fail;
  }
  map_addnode(m, node);
  m->nnodes++;
  return 0;
  fail:
  if (node) free(node);
  return -1;
}


void map_remove_(map_base_t *m, const char *key) {
  map_node_t *node, *prev;
  map_node_t **next = map_getref(m, key);
  if (next) {
    node = *next;
    *next = (*next)->next;

    
    // Remove from the order list
    if(m->head == node){
      m->head = node->oNext;
    }
    prev = previous_node(m, node);
    if(m->tail == node){
      m->tail = prev;
      prev->next = NULL;
    }

    free(node);
    m->nnodes--;
  }
}


map_iter_t map_iter_(map_base_t *m) {
  map_iter_t iter;
  iter.node = m->head;
  return iter;
}


const char *map_next_(map_iter_t *iter) {
  if (!iter->node) return NULL;
  const char *key = (char*) (iter->node + 1);
  iter->node = iter->node->oNext;
  return key;
}
