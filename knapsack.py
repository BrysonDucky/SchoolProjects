import os
import time
startTime = time.time()

# Knapsack brute force implementation

def knapsack_brute_force(weights, values, capacity):
    # Get the number of items
    n = len(weights)
    
    # Define a recursive helper function to compute the maximum value for a given weight capacity
    def knapsack_helper(W, wt, val, i):
        # Base case: if there are no items left or the capacity is zero, return zero
        if i == 0 or W == 0:
            return 0
        
        # If the weight of the current item is more than the remaining capacity, skip it
        if wt[i-1] > W:
            return knapsack_helper(W, wt, val, i-1)
        
        # Otherwise, return the maximum of two cases:
        # (1) nth item included
        # (2) not included
        else:
            return max(val[i-1] + knapsack_helper(W-wt[i-1], wt, val, i-1),
                       knapsack_helper(W, wt, val, i-1))
    
    # Call the helper function to compute the maximum value
    max_value = knapsack_helper(capacity, weights, values, n)
    
    # Return the maximum value
    return max_value


def knapsack_greedy(weights, values, capacity):
    # Check if total weight is greater than capacity
    total_weight = sum(weights)
    if total_weight <= capacity:
        return sum(values)

    # Calculate the efficiency value for each object
    eff_values = [(values[i] / weights[i], i) for i in range(len(weights))]

    # Sort the objects by decreasing efficiency value
    eff_values.sort(reverse=True)

    # Initialize the knapsack and total value
    knapsack = [0] * len(weights)
    total_value = 0

    # Fill the knapsack with objects in decreasing order of efficiency value
    for (eff, i) in eff_values:
        if weights[i] <= capacity:
            knapsack[i] = 1
            capacity -= weights[i]
            total_value += values[i]

    return total_value




if __name__ == '__main__':
# Define the input data

 weights = [2, 3, 4, 1, 5, 6, 7, 8, 9, 10]
 values = [4, 5, 10, 1, 7, 8, 12, 15, 20, 25]
 capacity = 20

# Call the knapsack_brute_force function to compute the maximum value
 max_value_brute_force = knapsack_brute_force(weights, values, capacity)

# Print the result
 print("Maximum value:", max_value_brute_force)

# Call the knapsack_greedy function to compute the maximum value
max_value_approximation = knapsack_greedy(weights, values, capacity)

# Print the result
print("Maximum value:", max_value_approximation)
 

