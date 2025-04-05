import re

def solveCase():
    with open('input.txt', 'r') as file:
        data = file.read()
    
    # Regular expression to match valid mul(X,Y), do(), and don't() instructions
    pattern = r'(mul\(\s*\d{1,3}\s*,\s*\d{1,3}\s*\)|do\(\)|don\'t\(\))'
    
    # Find all matches
    matches = re.findall(pattern, data)
    
    # Initialize the flag to keep track of whether mul instructions are enabled
    mul_enabled = True
    total_sum = 0
    
    # Process each match
    for match in matches:
        if match.startswith('mul'):
            if mul_enabled:
                # Extract the numbers and calculate the product
                numbers = re.findall(r'\d{1,3}', match)
                x, y = int(numbers[0]), int(numbers[1])
                total_sum += x * y
        elif match == 'do()':
            mul_enabled = True
        elif match == "don't()":
            mul_enabled = False
    
    # Print the result
    print(f"Solution: {total_sum}")

# Call the function to solve the case
solveCase()