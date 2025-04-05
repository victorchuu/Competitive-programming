def is_safe_report(levels):
    increasing = all(levels[i] < levels[i + 1] and 1 <= levels[i + 1] - levels[i] <= 3 for i in range(len(levels) - 1))
    decreasing = all(levels[i] > levels[i + 1] and 1 <= levels[i] - levels[i + 1] <= 3 for i in range(len(levels) - 1))
    return increasing or decreasing

def is_safe_with_dampener(report):
    levels = list(map(int, report.split()))
    if is_safe_report(levels):
        return True
    for i in range(len(levels)):
        if is_safe_report(levels[:i] + levels[i+1:]):
            return True
    return False

def count_safe_reports(data):
    reports = data.strip().split('\n')
    safe_count = sum(1 for report in reports if is_safe_with_dampener(report))
    return safe_count

def solveCase():
    with open('input.txt', 'r') as file:
        data = file.read()
    safe_count = count_safe_reports(data)
    print(f"Solution: {safe_count}")

# Call the function to solve the case
solveCase()