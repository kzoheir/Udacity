#include <uWS/uWS.h>
#include <iostream>
#include "json.hpp"
#include "PID.h"
#include <math.h>

// for convenience
using json = nlohmann::json;

// For converting back and forth between radians and degrees.
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }
double max_throttle = 0.3;
double min_cte=0.0;
double max_cte=0.0;
// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
// else the empty string "" will be returned.
std::string hasData(std::string s) {
  auto found_null = s.find("null");
  auto b1 = s.find_first_of("[");
  auto b2 = s.find_last_of("]");
  if (found_null != std::string::npos) {
    return "";
  }
  else if (b1 != std::string::npos && b2 != std::string::npos) {
    return s.substr(b1, b2 - b1 + 1);
  }
  return "";
}

int main()
{
  uWS::Hub h;


  PID pid;
  // TODO: Initialize the pid variable.
  // Proportional - Integration - diffrentiation

  // First attempt: Sebastian settings:
    //pid.Init(0.2, 0.004, 3.0); max_throttle = 0.3;// Oscillating and touch the yellow line: Increase 'd'
    //pid.Init(0.2, 0.004, 5.0); max_throttle = 0.3;// Still Oscillating and touch the yellow line whrn i_error is high specially -ve: Increase 'd'and lower 'i';

    //pid.Init(0.2, 0.001, 6.0); max_throttle = 0.3; // less oscillation and touchs the line. Increase 'p'
    // pid.Init(0.3, 0.001, 6.0); max_throttle = 0.3; // Oscillation and do not touchs the line. Increase 'd'
    // pid.Init(0.3, 0.001, 7.0); max_throttle = 0.3; // Almost touched the line once. Increase 'd'
    // pid.Init(0.4, 0.001, 7.0); max_throttle = 0.3; // still oscillating. There is no point of incresing the 'd' go back to 5.5
    // pid.Init(0.5, 0.001, 5.5); max_throttle = 0.3; // Although it didn't touch any line. But high oscillation and big error to the left. Likely the road was large!
    // pid.Init(0.5, 0.001, 8.0); max_throttle = 0.3; // Acceptable. Try much higher 'p'
    // pid.Init(0.5, 0.001, 20.0); max_throttle = 0.3; // Acceptable.Min CTE: -0.8106 Max CTE: 1.0175. i_error seems to be stable -> good Ki
    // pid.Init(0.5, 0.001, 40.0); max_throttle = 0.35; // Oscillating. Even near boarder -> 'd' is too high .Min CTE: -2.3 Max CTE: 1.17
    pid.Init(0.5, 0.001, 10.0); max_throttle = 0.35; // Acceptable Oscillating. Min CTE: -1.7992 Max CTE: 1.7404
    h.onMessage([&pid](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, uWS::OpCode opCode) {
    // "42" at the start of the message means there's a websocket message event.
    // The 4 signifies a websocket message
    // The 2 signifies a websocket event
    if (length && length > 2 && data[0] == '4' && data[1] == '2')
    {
      auto s = hasData(std::string(data).substr(0, length));
      if (s != "") {
        auto j = json::parse(s);
        std::string event = j[0].get<std::string>();
        if (event == "telemetry") {
          // j[1] is the data JSON object
          double cte = std::stod(j[1]["cte"].get<std::string>());
          double speed = std::stod(j[1]["speed"].get<std::string>());
          double angle = std::stod(j[1]["steering_angle"].get<std::string>());
          double steer_value;
           /*
          * TODO: Calcuate steering value here, remember the steering value is
          * [-1, 1].
          * NOTE: Feel free to play around with the throttle and speed. Maybe use
          * another PID controller to control the speed!
          */         
          // Update error values with cte
          pid.UpdateError(cte);
          // Calculate steering value (if reasonable error, returns between [-1, 1])
          steer_value = pid.TotalError(cte, speed, angle); // Add cte, speed and angle just for debugging
          
          // DEBUG
          if (cte > max_cte) {
            max_cte = cte;
          }
          if (cte < min_cte) {
            min_cte = cte;
          }
          std::cout << std::endl << "CTE: " << cte << "Min CTE: " << min_cte << "Max CTE: " << max_cte << " Steering Value: " << steer_value << std::endl;

          json msgJson;
          msgJson["steering_angle"] = steer_value;
          // Setting throttle with same PID controller as steering
          // Formula below switches to between [0, 1], larger steering angle means less throttle
          // Multiplied by 0.5 for safety reasons
          msgJson["throttle"] = max_throttle;

          auto msg = "42[\"steer\"," + msgJson.dump() + "]";
          std::cout << msg << std::endl;
          ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
        }
      } else {
        // Manual driving
        std::string msg = "42[\"manual\",{}]";
        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      }
    }
  });

  // We don't need this since we're not using HTTP but if it's removed the program
  // doesn't compile :-(
  h.onHttpRequest([](uWS::HttpResponse *res, uWS::HttpRequest req, char *data, size_t, size_t) {
    const std::string s = "<h1>Hello world!</h1>";
    if (req.getUrl().valueLength == 1)
    {
      res->end(s.data(), s.length());
    }
    else
    {
      // i guess this should be done more gracefully?
      res->end(nullptr, 0);
    }
  });

  h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
    std::cout << "Connected!!!" << std::endl;
  });

  h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, char *message, size_t length) {
    ws.close();
    std::cout << "Disconnected" << std::endl;
  });

  int port = 4567;
  if (h.listen(port))
  {
    std::cout << "Listening to port " << port << std::endl;
  }
  else
  {
    std::cerr << "Failed to listen to port" << std::endl;
    return -1;
  }
  h.run();
}
