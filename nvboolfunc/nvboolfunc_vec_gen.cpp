#include "nvboolfunc.h"

//	nvboolfunc vector generate

//	This algorithm calculates all possible vectors for a given MAXIMUM input vector. Therefore, if the input vectors
//	have k-values of k = (3, 5, 2), the maximum input vector will be (2, 4, 1).
//	The number of vectors that are generated will be the product of all k-values multiplied against each other.
//	Therefore, using the last example, the number of vectors will be: 3 * 5 * 2 = 30.
void nvboolfunc_t::calculate_all_vectors(bit_vector_t max_vector, int max_hamming_norm, size_t max_vector_index)
{
	for (int i = max_vector_index; i >= 0; i--)
	{
		int value = max_vector[i];
		int decrement = 1;

		// decrement the value at the specific index until it is 0
		// add the copied vector to the list of all vectors
		// then, recurse on the copied vector on the next higher-order value
		while (value > 0)
		{
			bit_vector_t copy_vector(max_vector);
			copy_vector[i] -= decrement;
			int hamming_norm = max_hamming_norm - decrement;
			value = copy_vector[i];
			decrement++;

			// insert_copy vector into sorted_vectors by looping over possible vectors with the same mixed-base value (key)
			// then, insert based on what vector has higher order elements or greater higher order elements
			int key = calc_mb_value(copy_vector);
			bool higher_order = false;
			auto key_iter = all_vectors[hamming_norm].equal_range(key); // pair of two iterators; first points at before the range of the key; second points to after

			// iterate over every vector with the same key
			for (auto val_iter = key_iter.first; val_iter != key_iter.second && !higher_order; val_iter++)
			{
				// iterate over elements of the copy_vector and a vector with the same key
				// if copy_vector has greater elements, it is placed before the other vector
				for (int i = 0; i < kv_attributes.size(); i++)
				{
					if (val_iter->second[i] < copy_vector[i])
					{
						higher_order = true;
						all_vectors[hamming_norm].emplace_hint(val_iter, std::pair<int, bit_vector_t>(key, copy_vector)); // inserts before the vector that vec_iter points to
						break;
					}
					else if (val_iter->second[i] > copy_vector[i]) break;
				}
			}

			// insert at the end of the vectors with the same key (mixed-base value) if it is smaller
			if (!higher_order) all_vectors[hamming_norm].emplace_hint(key_iter.second, key, copy_vector);

			if (i > 0)
			{
				calculate_all_vectors(copy_vector, hamming_norm, i - 1);
			}
		}
	}
}

// calculate mixed base value
int nvboolfunc_t::calc_mb_value(bit_vector_t vector)
{
	int vector_value = 0;

	for (int i = 0; i < size - 1; i++)
	{
		vector_value += vector[i] * std::pow(kv_attributes[i], size - i - 2);
	}

	return vector_value;
}
