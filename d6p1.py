INPUT_SRC = "input.txt"


if __name__ == "__main__":

    input_text = ""
    with open(INPUT_SRC) as f:
        input_text = f.read()
        
    time_line, distance_line = input_text.split("\n")

    # split times
    times = []
    for i in time_line.split(" "):
        if i.isdigit():
            times.append(int(i))
            
    # split distances
    distances = []
    for i in distance_line.split(" "):
        if i.isdigit():
            distances.append(int(i))
            
            
    # find all possible ways to win
    output = 1
    for i in range(len(times)):
        time = times[i]
        total_ways = 0
        for s in range(time):
            # the button holded for s miliseconds
            distance = (time-s)*s
            if (distance > distances[i]):
                total_ways += 1
        output *= total_ways
        
    print("output:", output)