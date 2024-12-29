# Realistic System Optimization

## Optimizing Electric Motor Usage
### Problem overview
The task is to optimize the use of the electric motor in a plug-in-hybrid vehicle given the start battery level. The vehicle can switch between several different modes during the road:

1. Electric only
2. Mainly electric, with some gasoline
3. Mainly gasoline, with some electric
4. Gasoline only

The plan from start to end is already known and the path is divided into multiple segments. Each segment is one of the following type:

1. Motorway.
2. Country road.
3. Smaller road, hilly and/or winding.
4. Road in a sparsely populated urban area (small town or suburb).
5. Road in the city center (traffic lights, lots of starts and stops).

Comment: driving with gasoline only will of course not drain any battery. However, using gasoline only will cost more (in an enviromental perspective). 

### Solution
Dynamic programming (bottom up). Why? Because each segment has multiple possible driving modes, and the best choice depends on the current battery level and the segments remaining. Hence, we can explore all the possible combinations without redudant calculations. 

Time complexity:
O(nlink * start_battery * 4)


### Result
![image](https://github.com/user-attachments/assets/4ec3d649-d84d-4e83-80ae-be6e9de9b8b7)

![image](https://github.com/user-attachments/assets/215cbc41-1292-45da-a514-e5a45f98b6e1)

