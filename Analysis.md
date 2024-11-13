## Analysis

1. Were you able to generate something close to what the example showed? Why or why not.
    Yes and no, the results recieved are not the same for one because the time to sort does not reach 12000 milliseconds, so the graph is smaller
    and two, they are a little more sporatic, likely due to me running the program on codespaces rather than a dedicated machine. 

2. Did you see a slow down at some point why or why not?
    No, though it did speed up as more threads were being used, it was a marginal difference at best and did not effect the percieved slowness of the program running. 

3. Did your program run faster and faster when you added more threads? Why or why not?
    yes, but only to a certain point. After a while the gains were negligable, or even worse than the optimal amount of threads, which ended up being around 10. Not
    only because again, running on the virtual environment, but because after a certain time there was only so much the new threads could help with. 

4. What was the optimum number of threads for your machine?
    The optimum amount of threads came out to about 9 threads for the codespaces environment. Other thread amounts came close as well, but this seemed to be the best. 

5. What was the slowest number of threads for your machine?
    Funny enough, 2 threads was the slowest, and I believe its because trying to split it up and relying only on 2 threads to attack the problem with the creation and joining, was actually harmful instead of helpful. As more threads were added, more bandwith was provided and it was easier for the system to handle multiple tasks at once. 

![image](https://github.com/user-attachments/assets/56fce162-d50e-45b9-aa9e-0950e7643a8a)
    
