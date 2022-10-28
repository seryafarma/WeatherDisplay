# WeatherDisplay
Let's display the current weather and how is the forecast for the next few days?

## Hardware
The hardware utilizes a simple Wemos D1 board and 4x8x8 dot matrix module. It is simply using one SPI connection from the Wemos D1 to the module. The board needs to be connected to the internet to fetch the data.

## Software
The software will be arranged a bit such that it is following a good design (and not just putting everything in one big file). The state diagram and class diagram are shown below.

### State Diagram
V1.0 
- Initialize all the hardware
- Fetch the weather data.
- Display the weather data and set the timeout for the next fetch.
- In case there is error, for now stay in error mode.

In order to formalize things a bit, the state diagram of the weather is as follows:
![github_state_diagram](https://github.com/seryafarma/WeatherDisplay/blob/main/state_diagram.png)

### Class Diagram
To be added

## Utilities
Simple source files are added to _test_ the boards and connections. You can use them separately.
