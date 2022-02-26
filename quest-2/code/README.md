# Code Readme

Please describe what is in your code folder and subfolders. Make it
easy for us to navigate this space.

#### CanvasJS

Contains the html code to display the graph, developed by Keven.

The html script formats the chart following the specifications given in the prompt. A function named updateChart is used to periodacally fetch data as the backend node script parses it and sends it in. JQuery is used to recieve the data. In the rendered chart, the three sensor datas are plotted in different colors as displayed in the legend. A break is placed in the y-axis since the thermistor readings are generally higher numbers than the ultrasonic and IR sensors (since the latter two are in meters). This allows for better readability. The x-axis simply displays the time that the data was polled.

#### BrianCode

Contains the JavaScript code that receives information from serialport, parses it, and sends to html. Developed by Brian.

#### SuperCode

IDF program that drives the thermistor, ultrasonic, and IR sensors. Developed by Ayrton.

This code is a heavily modified version of the standard adc. It duplicates channels and characteristics and the equations used to find the Vout of each sensor. After the additions made to allow readings from multiple esp32 pins at once all the equations used in the skills for the sensors were added to code so they could each break down their own voltage calculations into measurable Engineering units.

#### Resources:
- https://canvasjs.com/javascript-charts/line-chart-axis-scale-breaks/
- https://canvasjs.com/html5-javascript-dynamic-chart/
- Past skills
