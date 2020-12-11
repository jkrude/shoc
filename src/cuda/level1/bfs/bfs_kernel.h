#ifndef BFS_KERNEL_H_
#define BFS_KERNEL_H_

#include<cuda.h>

#define get_queue_index(tid) ((tid%NUM_P_PER_MP))
#define get_queue_offset(tid) ((tid%NUM_P_PER_MP)*W_Q_SIZE)

struct BFS_kernel_warp{
    template<typename TAcc>
    void operator()(
        TAcc const & acc,
        unsigned int *levels,
        unsigned int *edgeArray,
        unsigned int *edgeArrayAux,
        int W_SZ,
        int CHUNK_SZ,
        unsigned int numVertices,
        int curr,
        int *flag ) const;
};

struct BFS_kernel_one_block{
    template<typename TAcc>
    ALPAKA_FN_ACC void operator()(
        TAcc const& acc,
        volatile unsigned int *frontier,
        unsigned int frontier_len,
        volatile unsigned int *cost,
        volatile int *visited,
        unsigned int *edgeArray,
        unsigned int *edgeArrayAux,
        unsigned int numVertices,
        unsigned int numEdges,
        volatile unsigned int *frontier_length,
        unsigned int num_p_per_mp,
        unsigned int w_q_size) const;
};

struct BFS_kernel_SM_block{
    template<typename TAcc>
    ALPAKA_FN_ACC void operator()(
        TAcc const& acc,
        volatile unsigned int *frontier,
        volatile unsigned int *frontier2,
        unsigned int frontier_len,
        volatile unsigned int *cost,
        volatile int *visited,
        unsigned int *edgeArray,
        unsigned int *edgeArrayAux,
        unsigned int numVertices,
        unsigned int numEdges,
        volatile unsigned int *frontier_length,
        unsigned int num_p_per_mp,
        unsigned int w_q_size) const;
};


struct BFS_kernel_multi_block{
    template<typename TAcc>
    ALPAKA_FN_ACC void operator()(
        TAcc const& acc,
        volatile unsigned int *frontier,
        volatile unsigned int *frontier2,
        unsigned int frontier_len,
        volatile unsigned int *cost,
        volatile int *visited,
        unsigned int *edgeArray,
        unsigned int *edgeArrayAux,
        unsigned int numVertices,
        unsigned int numEdges,
        volatile unsigned int *frontier_length,
        unsigned int NUM_P_PER_MP,
        unsigned int W_Q_SIZE);
};

struct Reset_kernel_parameters{
    template<typename TAcc>
    ALPAKA_FN_ACC void operator()(
        TAcc const& acc,
        unsigned int *frontier_length) const;
};


struct Frontier_copy{
    template<typename TAcc>
    ALPAKA_FN_ACC void operator()(
        TAcc const& acc,
        unsigned int *frontier,
        unsigned int *frontier2,
        unsigned int *frontier_length) const;
};

struct BFS_kernel_one_block_spill{
    template<typename TAcc>
    ALPAKA_FN_ACC void operator()(
        TAcc const& acc,
        volatile unsigned int *frontier,
        unsigned int frontier_len,
        volatile unsigned int *cost,
        volatile int *visited,
        unsigned int *edgeArray,
        unsigned int *edgeArrayAux,
        unsigned int numVertices,
        unsigned int numEdges,
        volatile unsigned int *frontier_length,
        const unsigned int max_mem) const;
};

struct BFS_kernel_SM_block_spill{
    template<typename TAcc>
    ALPAKA_FN_ACC void operator()(
        TAcc const& acc,
        volatile unsigned int *frontier,
        volatile unsigned int *frontier2,
        unsigned int frontier_len,
        volatile unsigned int *cost,
        volatile int *visited,
        unsigned int *edgeArray,
        unsigned int *edgeArrayAux,
        unsigned int numVertices,
        unsigned int numEdges,
        volatile unsigned int *frontier_length,
        const unsigned int max_mem) const ;
};

struct BFS_kernel_multi_block_spill{
    template<typename TAcc>
    ALPAKA_FN_ACC void operator()(
        TAcc const& acc,
        volatile unsigned int *frontier,
        volatile unsigned int *frontier2,
        unsigned int frontier_len,
        volatile unsigned int *cost,
        volatile int *visited,
        unsigned int *edgeArray,
        unsigned int *edgeArrayAux,
        unsigned int numVertices,
        unsigned int numEdges,
        volatile unsigned int *frontier_length,
        const unsigned int max_mem) const;
};




#endif        //BFS_KERNEL_H
