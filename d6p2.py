INPUT_SRC = "input.txt"


if __name__ == "__main__":

    input_text = ""
    with open(INPUT_SRC) as f:
        input_text = f.read()
        
    time_line, distance_line = input_text.split("\n")

    # find total time
    total_time = 0
    for i in time_line:
        if i.isdigit():
            if total_time == 0:
                total_time = int(i)
            else:
                total_time = total_time*10+int(i)
            
    # find total distance
    total_distance = 0
    for i in distance_line:
        if i.isdigit():
            if total_distance == 0:
                total_distance = int(i)
            else:
                total_distance = total_distance*10+int(i)
            
    # find all possible ways to win
    output = 1
    total_ways = 0
    for s in range(total_time):
        # the button holded for s miliseconds
        distance = (total_time-s)*s
        if (distance > total_distance):
            total_ways += 1
    output *= total_ways
        
    print("output:", output)