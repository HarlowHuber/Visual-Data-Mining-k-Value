#include "nvboolfunc.h"

//	nvboolfunc vector generate

//	This algorithm calculates all possible vectors for a given MAXIMUM input vector. Therefore, if the input vectors
//	have k-values of k = (3, 5, 2), the maximum input vector will be (2, 4, 1).
//	The number of vectors that are generated will be the product of all k-values multiplied against each other.
//	Therefore, using the last example, the number of vectors will be: 3 * 5 * 2 = 30.
void nvboolfunc_t::calculate_all_vectors(bit_vector_t max_vector, int max_hamming_norm, size_t max_vector_index)
{
	size_t last_index = max_vector.get_size() - 1;

	for (size_t i = max_vector_index; i < size - 1; i++)
	{
		size_t value = max_vector[i];
		size_t decrement = 1;

		// decrement the value at the specific index until it is 0
		// add the copied vector to the list of all vectors
		// then, recurse on the copied vector if the value is not the last value, 
		// and if the value at the last index is greater than 0
		while (value > 0)
		{
			bit_vector_t copy_vector(max_vector);
			copy_vector[i] -= decrement;
			int hamming_norm = max_hamming_norm - decrement;
			value = copy_vector[i];
			decrement++;
			all_vectors[hamming_norm].insert(std::pair<int, bit_vector_t>(calc_mb_value(copy_vector), copy_vector));

			if (i < last_index && copy_vector[last_index] > 0)
			{
				calculate_all_vectors(copy_vector, hamming_norm, i + 1);
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
