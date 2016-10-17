//Artificial Intelligence
void AI_follow(unsigned char agent, int agentNumber, unsigned char object, int objectNumber);//Moves agent to a specified object
void AI_avoid(unsigned char agent, int agentNumber, unsigned char object, int objectNumber);//Moves agent away from a specified object
void AI_shoot(unsigned char agent, int agentNumber, unsigned char object, int objectNumber);//Agent fires projectile at specified object
void AI_mimic(unsigned char agent, int agentNumber, unsigned char object, int objectNumber);//Copies the movement of another agent.
void AI_signal(unsigned char message);//Broadcast a signal to communicate with other agents.
void AI_listen();//Receives signals from other agents.
void AI_spin(unsigned char agent, int agentNumber, unsigned char direction, double amount);//agent rotates
void AI_catch(unsigned char agent, int agentNumber, unsigned char object, int objectNumber);//agent moves anticipating approaching target
void AI_travel(unsigned char agent, int agentNumber, double toXPosition, double toYPosition, double Velocity);//agent moves to a point
