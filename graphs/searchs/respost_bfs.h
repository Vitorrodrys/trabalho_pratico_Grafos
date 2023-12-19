//
// Created by vitor on 12/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_RESPOST_BFS_H
#define TRABALHO_PRATICO_GRAFOS_RESPOST_BFS_H
#include "../../generic_structs/linked_list/linked_list.h"

typedef struct RespostSearchBFS RespostSearchBFS;
//A TAD that assists in analyzing the response of a previously executed BFS or can also assist in the process of constructing the BFS response.





/**
* create a intance of RespostSearchBFS
* @param tam_graph: quantity of vertex of the graph
* @param which_vertex: vertex origin of the search
* @return the new instance of RespostSearchBFS
 */
RespostSearchBFS *create_respost(int tam_graph, int which_vertex);

/**
 * clear a instance of RespostSearchBFS of the memory
 * @param self: instance of the object
 * @return NULL
 */
RespostSearchBFS *destroy_respost(RespostSearchBFS *self);




/**
 * Mark the vertex 'to' as visiting, indicating that to arrive at 'to,' one should pass through 'from.'
 * Update the distance to 'to' as the sum of the distance from 'from' plus the distance from 'to' itself.
 * @param self: instance of RespostSearchBFS
 * @param from: exit vertex to arrive in 'to'
 * @param to: new vertex that will be included
 * @param dist: distance of 'from' to 'to'
 * @return If 'from' and 'to' represent vertices within the graph, return true, because the information about this vector could be handled within the struct.
   Otherwise, return false. Internally, to determine if 'from' and 'to' are graph vertices, the function only checks if 'from' and 'to' are
   less than the size of the graph (quantity of vertices).
 */
int resbfs_to_visite_element(RespostSearchBFS *self, int from, int to, double dist);


/**
 * get the next vertex of the queue of the BFS
 * @param self : Instance of RespostSearchBFS
 * @return the next element that the BFS should get the direct connections
 */
int resbfs_get_next_vertex_queue(RespostSearchBFS *self);

/**
 * check if the queue of the RespostSearchBFS is empity
 * @param self: Instance of RespostSearchBFS
 * @return true if the queue is empity, and false otherwise
 */
int resbfs_queue_is_void(RespostSearchBFS *self);


/**
 * check if the BFS still don't visited an element
 * @param self: instance of RespostSearchBFS
 * @param elem: element that want check if was do visited
 * @return true if still don't was visited, and false otherwise
 */
int resbfs_elem_still_not_visited(RespostSearchBFS *self, int elem);

/**
 * transforming an instance of RespostSearchBFS in one string
 * @param self: instance of RespostSearchBFS
 * @return String
 */
char *resbfs_str(RespostSearchBFS *self);

/**
 * Generate a path that starts from the origin and reaches a specified vertex using an instance of RespostSearchBFS previously generated
 * @param self: Instance of RespostSearchBFS
 * @param what_vertex: vertex that should be the end of the path
 * @return A list that contains the sequence of vertices to be visited to go from the origin and reach 'what_vertex,' in reverse order.
 * In other words, starting from 'what_vertex' and going backward, the sequence would be what_vertex, x, y, z, origin_vertex.
 */
LinkedList *resbfs_mount_way_to_vertex(RespostSearchBFS *self, int what_vertex);

/**
 * verify within of an instance of RespostSearchBFS previously generated if this BFS can reaches a vertex received as parameter
 * @param self: Instance of RespostSearchBFS
 * @param vertex: vertex that want verify if exist a path for it
 * @return true if exist a path, and false otherwise
 */
int resbfs_exist_a_way_to_vertex(RespostSearchBFS *self, int vertex);

/**
 * verify if the remotion of 'half_vertex' make with that some path don't be more possible
 * @param self: instance pf RespostSearchBFS
 * @param half_vertex: vertex that should be unconsidered if found in some path
 * @param to: vertex that is the end of the path between origin vertex within RespostSearchBFS and to
 * @return true if 'half_vertex' obstructs the path, false otherwise.
 */
int resbfs_check_if_middle_path_contains_vertex(RespostSearchBFS *self, int half_vertex, int to);
#endif //TRABALHO_PRATICO_GRAFOS_RESPOST_BFS_H
