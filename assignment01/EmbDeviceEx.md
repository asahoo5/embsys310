Embedded Device Example:
------------------------
SmartWatch (ex: iWatch), which is kind of complex hardware to make fit many componenets in a tiny space. 
It uses a System on Chip (SoC) as its main CPU, which runs Watch Operating System and supports Applications on it. 
Along with it, it has multiple sensors to support different features (Like accelometer, gyroscope, magnetometer (common in most wearables), heart rate monitor, 
barometeric pressure meter (one that calculates number of flights climbed feature in iWatch/FitBit) and many more).
It also utilizes bluetooth/Wifi chip module to communicate with smartphones for communicating its data and upgrade software path. 
Few wearable like Gramin do have GPS modules embedded in it for location tracking feature.

As discussed in Telegraph Example, SmartWatch goes through similar development challenges:

1. ThroughPut - handling sensors data which are generated continuously, while supporting multiple application tasks.
2. Memory - Considering size of the device, it can't afford to support huge memory.
	    Big Storage Constraint! It has to buffer sensor data and dump it to linked smartphone time to time.
	    Also have RAM constraints! Have to carefully decide on application and kernel space utilization.
3. Response - Certain sensor datas like Heart rate monitor, are highly sensitive - device needs to be capable enough to process, analyze and report data in time.
	      Also, response time for it's sensor data (steps, flights climbed, current location) determines the product quality.
4. Testability - Requires a development platform for prototyping and emulation platform to perform integration testing.
5. Debugability - Depending on Platform/Processor selected for the product, requires developer to identify necessory development and debug related (JTAGs) environment & tools (ex: IDE, Compiler, Requirement Tracing, Test Automation, etc.)
6. Security - Requirements and actions for device security, since user data is critical and can lead to legal actions.
	      Propreitery Security!
7. Power Consumption - A proper hardware/software tradeoff task - requires to identify device usecase, device idle/active time, device application, Processor/Sensor/ASICs power dissipation and other critical factors to determine overall consumption.
		       A critical factor for the device!
8. BOM Cost - Requires to optimally select the components for the device. Factor reduce cost of the device and generate profit to organization.
9. Reliability - Software/Hardware Quality and Performance Reliability - to reduce maintainence efforts.
10. Program Installation and Upgrade path for future software release (Bluetooth feature for upgrade & some internal ports for Failure & Measurement Effectiveness Analysis (non-user accessible debugging and analysis feature for maintenance))
