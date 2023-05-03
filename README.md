# Drone Simulation System (Team 19, 010)

## Team Information
Team Number: 19

Member Names: Chiemeka Nwakama, Emma Ulrich, Madeline Mcginnis, Nicholas Horst

Member x500s: nwaka013, ulric244, mcgin374, horst105

## Project Overview
### What is this project about?
This is a drone simulation system, modeling that of a transportation oriented service (like Uber, Lyft, etc.). The drone acts as a taxi, and picks up robots placed around the map that need to get from a point A to a point B. 

The drone can follow several different movement paths using different algorithms such as dijkstra's, DFS, Beeline, and A*. Based on the chosen movement algorithm, the drone will move to these points and complete trips accordingly. 

### How do you run the simulation?

From the original readme:

Here is a quick overview of how to run the visualization (If you are using ssh, navigate to ssh category below):

    ```bash
    # Go to the project directory
    cd /path/to/repo/project
    
    # Build the project
    make -j
    
    # Run the project (./build/web-app <port> <web folder>)
    ./build/bin/transit_service 8081 apps/transit_service/web/
    ```
    
Navigate to http://127.0.0.1:8081 and you should see a visualization.

Navigate to http://127.0.0.1:8081/schedule.html and you should see a page to schedule the trips.

*Note: 8081 will depends on what port you used. If you use port 8082, then it will be http://127.0.0.1:8082 instead.*

### Schedule
You will be able to schedule the robots for a ride in this page http://127.0.0.1:8081/schedule.html. 

Type passenger name, select start and end destination, and press `Schedule Trip` button to schedule a trip. 

Now go to 3D Visualization page and select the view of the entities on top right corner.

### 3D Visualization
You will be able to watch the simulation of the drone and the passenger here http://127.0.0.1:8081.

On top right corner, you can change your camera view into locking the entities.

### Build and run in different environments:

### Getting Started using SSH onto CSE Lab machines

**Important: You have to start the ssh clean if you would like to use the commands below. This means, if you are currently using vscode and already login via ssh, then you cannot run the commands below.**

1. SSH into a CSE Lab Machine using **port forwarding** for the UI

   **Note:** If port `8081` is not available, choose a different port (e.g. 8082, 8083, etc...)

    ```bash
    ssh -L 8081:127.0.0.1:8081 x500@csel-xxxx.cselabs.umn.edu
    ```
    
    Example:
    ```bash
    ssh -L 8081:127.0.0.1:8081 kaung006@csel-kh1250-05.cselabs.umn.edu
    ```

2. Compile the project (within ssh session)

    ```bash
    cd /path/to/repo/project
    make -j
    ```
    
 3. Run project (within ssh session)

    ```bash
    ./build/bin/transit_service 8081 apps/transit_service/web/
    ```

5. Navigate to http://127.0.0.1:8081 and you should see a visualization.

6. Navigate to http://127.0.0.1:8081/schedule.html and you should see a page to schedule the trips.

### Using VOLE

1. See [here](https://github.umn.edu/umn-csci-3081-S23/FAQs/tree/main/VOLE) on how to start using VOLE.

2. Compile the project (within ssh session)

    ```bash
    cd /path/to/repo/project
    make -j
    ```
    
  3. Run project (within ssh session)

      ```bash
      ./build/bin/transit_service 8081 apps/transit_service/web/
      ```

  4. Navigate to http://127.0.0.1:8081 and you should see a visualization.

  5. Navigate to http://127.0.0.1:8081/schedule.html and you should see a page to schedule the trips.

## What does the simulation do specifically?

While overall layout is better laid out in the attached UML and .cc files, a general overview can be seen here:

<ul>
    <li> All IEntity objects are located on the same physical plane: a map of the University of Minnesota - Minneapolis Campus.
    <li> The visible and interactable IEntity objects are:
     <ol>
        <li> Drones: The transportation vehicles to carry robots from one location to another.
        <li> Robots: The transportable placeholders that represent people.
        <li> Helicopter: A helicopter flies around the map, adding realism to our simluation.
        <li> Banks: Drones must stop at banks periodically to deposit funds, more on this below.
     </ol>
    <li> As previously decribed, the user must schedule trips on the separate scheduler window. They do this by naming their trip, choosing their movement strategy (Dijkstra's, DFS, etc.), and selecting their pickup and dropoff locations on the map.
    <li> After pressing the "Schedule Trip" button on the scheduler window, the robots will appear in the simulation with the drone on its way. Because the drone is already present on the map waiting for trips, it will not spawn in/out when scheduling trips.
</ul>

## New Features
#### Factory/Decorator
<ul>
    <li> What does it do?
    <li> Why is it significantly interesting?
    <li> How does it add to the existing work?
    <li> Which design pattern did you choose to implement it with and why?
    <li> Instructions to use this new feature:
</ul>

#### Singleton
<ul>
    <li> What does it do?
     <ol>
        <li> Our singleton implementation collects important data from the deliveries to be outputted and analyzed into a CSV file.
     </ol>
    <li> Why is it significantly interesting?
     <ol>
        <li> For those who do not have a passion for viewing and analyzing data, the trends and analysis that can be gathered from this data can be vital to employers, employees, and customers of any transportation service.
     </ol>
    <li> How does it add to the existing work?
     <ol>
        <li> It adds by producing important data and insights that is not easily available in the default simulation. Again, insights can be gathered to make important decisions about trip distances, monetary rates, etc.
     </ol>
    <li> Which design pattern did you choose to implement it with and why?
     <ol>
        <li> We decided to use singleton to collate all data collection into one centralized object. Through having a collection of std::map's, all data collected from the simulation can located in one space, where it can also be analzyed and put into the CSV file. Whenever the DataCollection class is initialized and called (no matter what kind of data is being processed), it is easy to send and store important numbers and trends.
     </ol>
    <li> Instructions to use this new feature:
     <ol>
        <li> There is a writeToCSV button that can be pressed at any time to update/add data to the existing CSV file present in the code. Other than the user being able to update and view the collected data, all processing will be done automatically.
     </ol>
</ul>

## Sprint Retrospectives
#### Sprint 1 (4/11 - 4/21)
<ul>
    <li> What went well?
        <ol>
            <li> Communication went really well for us right off the bat. The group chat we have was always very talkative, and we did a great job on assiging tasks and helping out wherever help was needed.
        </ol>
    <li> What didn't go well?
        <ol>
            <li> Implementation of the wallet in conjunction with the banks is turning out to be a little more complicated than we expected.
        </ol>
    <li> What can we get better at?
        <ol>
            <li> Office hours is going to be a tool we are going to use a lot throughout this project. We will get better at checking in with TA's and making sure we are on the right direction, code-wise.
        </ol>
</ul>

#### Sprint 2 (4/22 - 4/28)
<ul>
    <li> What went well?
        <ol>
            <li> Starting the data collection integration was straightforward. We got a good start on it, and it shouldn't be a huge problem to finish as we continue development.
        </ol>
    <li> What didn't go well?
        <ol>
            <li> Merging the wallet + bank integration in with the data collection may prove to be an issue. Syntactical and logical issues may prove difficult for us when finishing out the project.
        </ol>
    <li> What can we get better at?
        <ol>
            <li> We did a good job of attending office hours throughout the sprint, but could probably go even more. More help from knowledgable TA's will always help us.
        </ol>
</ul>

#### Sprint 3 (4/29 - 5/5)
<ul>
    <li> What went well?
    <li> What didn't go well?
    <li> What can we get better at?
</ul>
