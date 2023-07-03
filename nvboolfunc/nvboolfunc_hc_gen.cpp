/*
Hansel Chain Generation

Author: Bridget Smith
Edits: Harlow Huber

*/
#include "nvboolfunc.h"


void nvboolfunc_t::calculateHanselChains(int vector_dimension)
{
    // For n dimensions, iterate through to generate chains and
    for (int dim_num = 0; dim_num < vector_dimension; dim_num++)
    {
        int num = kv_attributes[dim_num];

        // Need a base chain to use for genChains
        if (dim_num == 0)
        {
            //generate the base chain
            std::vector<bit_vector_t> baseChain;

            for (int k = 0; k < num; k++)
            {
                bit_vector_t b(vector_dimension);
                b[0] = k;
                b.setLevel();
                baseChain.push_back(b);
            }

            //create a std::vector of std::vectors to hold the baseChain
            hanselChainSet.push_back(baseChain);
        }
        else
        {
            std::unordered_map<int, std::vector<std::vector<bit_vector_t>>> chainNum;

            for (int k = 0; k < num; k++)
            {
                chainNum[k] = hanselChainSet;
            }

            hanselChainSet = genChains(num, vector_dimension, chainNum);
        }
    }
}

std::vector<std::vector<bit_vector_t>> nvboolfunc_t::genChains(int num, int vector_dimension, std::unordered_map<int, std::vector<std::vector<bit_vector_t>>> chain)
{
    std::unordered_map<int, std::vector<std::vector<bit_vector_t>>> chains = chain;

    //add key string "0","1",...,num to the beginning of each element in the corresponding key
    for (int j = 0; j < num; j++)
    {
        for (int k = 0; k < chains.at(j).size(); k++)
        {
            for (int l = 0; l < chains.at(j)[k].size(); l++)
            {
                bit_vector_t b(vector_dimension);
                b[0] = j;

                for (int i = 1; i < vector_dimension; i++)
                {
                    b[i] = chains.at(j)[k][l][i - 1];
                }

                b.setLevel();
                chains.at(j)[k][l] = b;
            }
        }
    }

    //move the largest of each sub std::vector to corresponding sub std::vector in the first key
    //then move the largest of each subsequent sub std::vector to the second key's sub std::vector
    //repeat until chain.at(num-2) is reached since the last key will have nothing moved 
    //to it
    //j = current key being added to
    //emptV = number of empty std::vectors
    for (int j = 0; j < chains.size() - 1; j++)
    {
        //count is to keep up with the elemental std::vector having elements removed/moved from
        for (int k = 0; k < chains.at(j).size(); k++)
        {
            //I think I need to make the code below recursive
            int count = j;

            for (count; count < chains.size() - 1; count++)
            {
                if (count + 1 >= chain.size())
                {
                    break;
                }

                /// USE FIND AND END because kth std::vector doesn't exist for 3d 3val, k=2
                if (k > chains.at(count + 1).size() - 1)
                {
                    break;
                }

                if (chains.at(count + 1).at(k).empty())
                {
                    //### DEAL WITH EMPTY std::vectorS~!###
                    //chains.at(to_string(count + 1)).at(k).erase();
                    break;
                }

                int end = chains.at(count + 1).at(k).size();

                //add last element from position k of key count+1 to position k of j
                chains.at(j)[k].push_back(chains.at(count + 1)[k].at(end - 1));

                //pop off the moved element
                chains.at(count + 1).at(k).pop_back();
            }
        }
    }

    //we need to prepare for the next iteration of i in the first for loop
    //by adding all chains together, then adding combined chains to each key
    for (int j = 1; j < num; j++) 
    {
        for (int k = 0; k < chains.at(j).size(); k++) 
        {
            chains.at(0).push_back(chains.at(j)[k]);
        }
    }

    for (int j = 0; j < num; j++) {
        chains.at(j) = chains.at(0);
    }

    std::vector<std::vector<bit_vector_t>> chainsTogether;

    return chainsTogether = chains.at(0);
}
