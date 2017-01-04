/*********************************************************************
*
* Software License Agreement (BSD License)
*
*  Copyright (c) 2010, ISR University of Coimbra.
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the ISR University of Coimbra nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*
* Author: Gonçalo Cabrita on 19/05/2010
*********************************************************************/

#include "cereal_port/CerealPort.h"
#include <netinet/in.h>
#include <set>
#include <map>

// OI Modes
#define OI_MODE_OFF                                 0
#define OI_MODE_PASSIVE                             1
#define OI_MODE_SAFE                                2
#define OI_MODE_FULL                                3

// Delay after mode change in ms
#define OI_DELAY_MODECHANGE_MS                      20

// Charging states
#define OI_CHARGING_NO                              0
#define OI_CHARGING_RECOVERY                        1
#define OI_CHARGING_CHARGING                        2
#define OI_CHARGING_TRICKLE                         3
#define OI_CHARGING_WAITING                         4
#define OI_CHARGING_ERROR                           5

// IR Characters
#define FORCE_FIELD                                 161
#define GREEN_BUOY                                  164
#define GREEN_BUOY_FORCE_FIELD                      165
#define RED_BUOY                                    168
#define RED_BUOY_FORCE_FIELD                        169
#define RED_BUOY_GREEN_BUOY                         172
#define RED_BUOY_GREEN_BUOY_FORCE_FIELD             173
#define VIRTUAL_WALL                                162

// Positions
#define ROOMBA_TWO_LEFT                             0
#define ROOMBA_TWO_RIGHT                            1

#define ROOMBA_FOUR_LEFT                            0
#define ROOMBA_FOUR_CENTER_LEFT                     1
#define ROOMBA_FOUR_CENTER_RIGHT                    2
#define ROOMBA_FOUR_RIGHT                           3

#define ROOMBA_SIX_LEFT                             0
#define ROOMBA_SIX_FRONT_LEFT                       1
#define ROOMBA_SIX_CENTER_LEFT                      2
#define ROOMBA_SIX_CENTER_RIGHT                     3
#define ROOMBA_SIX_FRONT_RIGHT                      4
#define ROOMBA_SIX_RIGHT                            5

#define ROOMBA_OMNI                                 2

#define ROOMBA_SIDE_MOTOR                           3
#define ROOMBA_MAIN_MOTOR                           2
#define ROOMBA_RIGHT_MOTOR                          1
#define ROOMBA_LEFT_MOTOR                           0

#define ROOMBA_RIGHT_ENCODER                        0
#define ROOMBA_LEFT_ENCODER                         1

#define ROOMBA_MAIN_BRUSH                           0
#define ROOMBA_SIDE_BRUSH                           1
#define ROOMBA_VACUUM                               2

// Buttons
#define BUTTON_CLOCK                                7
#define BUTTON_SCHEDULE                             6
#define BUTTON_DAY                                  5
#define BUTTON_HOUR                                 4
#define BUTTON_MINUTE                               3
#define BUTTON_DOCK                                 2
#define BUTTON_SPOT                                 1
#define BUTTON_CLEAN                                0

// LEDs
#define LED_WARNING                                 0
#define LED_DOCK                                    1
#define LED_SPOT                                    2
#define LED_DIRT                                    3
#define LED_CLEAN                                   4
#define LED_SUNDAY                                  5
#define LED_MONDAY                                  6
#define LED_TUESDAY                                 7
#define LED_WEDNESDAY                               8
#define LED_THURSDAY                                9
#define LED_FRIDAY                                  10
#define LED_SATURDAY                                11
#define LED_COLON                                   12
#define LED_PM                                      13
#define LED_AM                                      14
#define LED_CLOCK                                   15
#define LED_SCHEDULE                                16

// Roomba Dimensions
#define ROOMBA_BUMPER_X_OFFSET                      0.050
#define ROOMBA_DIAMETER                             0.330
#define ROOMBA_AXLE_LENGTH                          0.235

#define ROOMBA_MAX_LIN_VEL_MM_S                     500
#define ROOMBA_MAX_ANG_VEL_RAD_S                    2
#define ROOMBA_MAX_RADIUS_MM                        2000

//! Roomba encoder pulses to meter constant
#define ROOMBA_PULSES_TO_M                          0.000445558279992234

#define ROOMBA_ENCODER_OVERFLOW                     65535

namespace iRobot
{
	//! OI op codes
	/*!
	 * Op codes for commands as specified by the iRobot Open Interface.
	 */
	typedef enum _OI_Opcode {

		// Command opcodes
		OI_OPCODE_START = 128,
		OI_OPCODE_BAUD = 129,
		OI_OPCODE_CONTROL = 130,
		OI_OPCODE_SAFE = 131,
		OI_OPCODE_FULL = 132,
		OI_OPCODE_POWER = 133,
		OI_OPCODE_SPOT = 134,
		OI_OPCODE_CLEAN = 135,
		OI_OPCODE_MAX = 136,
		OI_OPCODE_DRIVE = 137,
		OI_OPCODE_MOTORS = 138,
		OI_OPCODE_LEDS = 139,
		OI_OPCODE_SONG = 140,
		OI_OPCODE_PLAY = 141,
		OI_OPCODE_SENSORS = 142,
		OI_OPCODE_FORCE_DOCK = 143,
		OI_OPCODE_PWM_MOTORS = 144,
		OI_OPCODE_DRIVE_DIRECT = 145,
		OI_OPCODE_DRIVE_PWM = 146,
		OI_OPCODE_STREAM = 148,
		OI_OPCODE_QUERY = 149,
		OI_OPCODE_PAUSE_RESUME_STREAM = 150,
		OI_OPCODE_SCHEDULE_LEDS = 162,
		OI_OPCODE_DIGIT_LEDS_RAW = 163,
		OI_OPCODE_DIGIT_LEDS_ASCII = 164,
		OI_OPCODE_BUTTONS = 165,
		OI_OPCODE_SCHEDULE = 167,
		OI_OPCODE_SET_DAY_TIME = 168

    } OIOpcode;


	//! OI packet id
	/*!
	 * Packet ids for sensors as specified by the iRobot Open Interface.
	 */
	typedef enum _OI_Packet_ID {
	
		// Sensor Packets
		OI_PACKET_GROUP_0 = 0,			//! OI packets 7-26
		OI_PACKET_GROUP_1 = 1,			//! OI packets 7-16
		OI_PACKET_GROUP_2 = 2,			//! OI packets 17-20
		OI_PACKET_GROUP_3 = 3,			//! OI packets 21-26
		OI_PACKET_GROUP_4 = 4,			//! OI packets 27-34
		OI_PACKET_GROUP_5 = 5,			//! OI packets 35-42
		OI_PACKET_GROUP_6 = 6,			//! OI packets 7-42
		OI_PACKET_GROUP_100 = 100,		//! OI packets 7-58
		OI_PACKET_GROUP_101 = 101,		//! OI packets 43-58
		OI_PACKET_GROUP_106 = 106,		//! OI packets 46-51
		OI_PACKET_GROUP_107 = 107,		//! OI packets 54-58
		OI_PACKET_BUMPS_DROPS = 7,
		OI_PACKET_WALL = 8,
		OI_PACKET_CLIFF_LEFT = 9,
		OI_PACKET_CLIFF_FRONT_LEFT = 10,
		OI_PACKET_CLIFF_FRONT_RIGHT = 11,
		OI_PACKET_CLIFF_RIGHT = 12,
		OI_PACKET_VIRTUAL_WALL = 13,
		OI_PACKET_WHEEL_OVERCURRENTS = 14,
		OI_PACKET_DIRT_DETECT = 15,
        OI_PACKET_UNUSED_16 = 16,
		OI_PACKET_IR_CHAR_OMNI = 17,
		OI_PACKET_BUTTONS = 18,
		OI_PACKET_DISTANCE = 19,
		OI_PACKET_ANGLE = 20,
		OI_PACKET_CHARGING_STATE = 21,
		OI_PACKET_VOLTAGE = 22,
		OI_PACKET_CURRENT = 23,
		OI_PACKET_TEMPERATURE = 24,
		OI_PACKET_BATTERY_CHARGE = 25,
		OI_PACKET_BATTERY_CAPACITY = 26,
		OI_PACKET_WALL_SIGNAL = 27,
		OI_PACKET_CLIFF_LEFT_SIGNAL = 28,
		OI_PACKET_CLIFF_FRONT_LEFT_SIGNAL = 29,
		OI_PACKET_CLIFF_FRONT_RIGHT_SIGNAL = 30,
		OI_PACKET_CLIFF_RIGHT_SIGNAL = 31,
        OI_PACKET_UNUSED_32 = 32,
        OI_PACKET_UNUSED_33 = 33,
		OI_PACKET_CHARGE_SOURCES = 34,
		OI_PACKET_OI_MODE = 35,
		OI_PACKET_SONG_NUMBER = 36,
		OI_PACKET_SONG_PLAYING = 37,
		OI_PACKET_STREAM_PACKETS = 38,
		OI_PACKET_REQ_VELOCITY = 39,
		OI_PACKET_REQ_RADIUS = 40,
		OI_PACKET_REQ_RIGHT_VELOCITY = 41,
		OI_PACKET_REQ_LEFT_VELOCITY = 42,
		OI_PACKET_RIGHT_ENCODER = 43,
		OI_PACKET_LEFT_ENCODER = 44,
		OI_PACKET_LIGHT_BUMPER = 45,
		OI_PACKET_LIGHT_BUMPER_LEFT = 46,
		OI_PACKET_LIGHT_BUMPER_FRONT_LEFT = 47,
		OI_PACKET_LIGHT_BUMPER_CENTER_LEFT = 48,
		OI_PACKET_LIGHT_BUMPER_CENTER_RIGHT = 49,
		OI_PACKET_LIGHT_BUMPER_FRONT_RIGHT = 50,
		OI_PACKET_LIGHT_BUMPER_RIGHT = 51,
		OI_PACKET_IR_CHAR_LEFT = 52,
		OI_PACKET_IR_CHAR_RIGHT = 53,
		OI_PACKET_LEFT_MOTOR_CURRENT = 54,
		OI_PACKET_RIGHT_MOTOR_CURRENT = 55,
		OI_PACKET_BRUSH_MOTOR_CURRENT = 56,
		OI_PACKET_SIDE_BRUSH_MOTOR_CURRENT = 57,
		OI_PACKET_STASIS = 58
	
    } OIPacketID;

	/*! \class OpenInterface OpenInterface.h "inc/OpenInterface.h"
	 *  \brief C++ class implementation of the iRobot OI.
	 *
	 * This class implements the iRobot Open Interface protocolor as described by iRobot. Based on the Player Roomba driver writen by Brian Gerkey.
	 */
	class OpenInterface
	{
		public:
	
		//! Constructor
		/*!
		 * By default the constructor will set the Roomba to read only the encoder counts (for odometry).
		 *
		 *  \sa setSensorPackets()
		 */
        OpenInterface();
		//! Destructor
		~OpenInterface();
	
		//! Open the serial port
		/*!
         *  \param serial_port      The name of the serial port where the Roomba is connected.
         *  \param baud_rate        The baudrate of the serial port. Default value is 115200.
         *  \param full_control     Whether to set the Roomba on OImode full or not. Defaults to true.
         *
         *  \sa closeSerialPort()
         *
         *  \return true if successful, false otherwise
		 */
        bool openSerialPort(std::string * serial_port, int baud_rate=115200, bool full_control=true);
		//! Close the serial port
        bool closeSerialPort();
	
		//! Power down the Roomba.
        bool powerDown();
	
		//! Set sensor packets
		/*!
		*  Set the sensor packets one wishes to read from the roomba. By default the constructor will set the Roomba to read only the encoder counts (for odometry). 
		*
        *  \param packets       Array of sensor packets to read.
        *  \param packets_size  Number of sensor packets.
		*
        *  \return true if successful, false otherwise
		*/
        bool setSensorPackets(OIPacketID * packets, unsigned int packets_size);
        bool setSensorPackets(std::vector<OIPacketID> &packets){return setSensorPackets(packets.data(), packets.size());}
		//! Read sensor packets
		/*!
		*  Requested the defined sensor packets from the Roomba. If you need odometry and you requested encoder data you need to call calculateOdometry() afterwords.
		*
		*  \param timeout		Timeout in milliseconds.
		*
        *  \sa calculateOdometry()
		*
        *  \return true if successful, false otherwise
		*/
        bool getSensorPackets(int timeout);
	
		//! Drive
		/*!
		*  Send velocity commands to Roomba.
		*
		*  \param linear_speed  	Linear speed.
		*  \param angular_speed  	Angular speed.
		*
        *  \return true if successful, false otherwise
		*/
        bool drive(double linear_speed, double angular_speed);
		//! Drive direct
		/*!
		*  Send velocity commands to Roomba.
		*
		*  \param left_speed  	Left wheel speed.
		*  \param right_speed  	Right wheel speed.
		*
        *  \return true if successful, false otherwise
		*/
        bool driveDirect(int left_speed, int right_speed);
	
		//! Set brushes
		/*!
		*  Set the various brushes motors.
		*
        *  \param brushes                The identifiers of the brushes to be changed.
        *  \param states                 The state of each brush in brushes.
        *  \param pwms                   The pwm for each brush in brushes.
        *  \param directions             Directions for the brushes (not used for the vacuum)
        *  \param size                   Size of the arrays.
		*
        *  \return true if successful, false otherwise
		*/
        bool setBrushes(unsigned char * brushes, bool * states, unsigned char * pwms, unsigned char * directions, unsigned int size);
		
		//! Set song
		/*!
		*  Record a song on Roombas memory. Songs can be played with playSong().
		*
		*  \param song_number 	Song id (from 0 to 15) so you can play it later.
		*  \param song_length  	Number of notes in the song.
		*  \param notes  		Array of notes.
		*  \param note_lengths  Array of notes length.
		*
		*  \sa playSong()
		*
        *  \return true if successful, false otherwise
		*/
        bool setSong(unsigned char song_number, unsigned char song_length, unsigned char *notes, unsigned char *note_lengths);
		//! Play song
		/*!
		*  Play a song previously recorded on Roombas memory. You can only play songs stored with setSong().
		*
		*  \param song_number 	Song id (from 0 to 15) so you can play it later.
		*
		*  \sa setSong()
		*
        *  \return true if successful, false otherwise
		*/
        bool playSong(unsigned char song_number);
	
		//! Set leds
		/*!
        *  Set the leds on the Roomba.
		*
        *  \param leds              Array that contains the identifiers of the LEDs to be changed.
        *  \param states            Array containning the new states for the LEDs.
        *  \param size              The size of leds and states.
        *  \param clean_color		Clean led color, varies from green (yellow, orange) to red.
        *  \param clean_brightness	Clean led intensity.
		*
        *  \return true if successful, false otherwise
		*/
        bool setLeds(unsigned int * leds, bool * states, unsigned int size, int clean_color=-1, int clean_brightness=-1);
        //! Set the seven segment display
		/*!
        *  Set the digit leds on the Roomba, the ones on the seven segment display. Digits are ordered from left to right on the robot.
		*
        *  \param digits 		Digits
		*
        *  \return true if successful, false otherwise
		*/
        bool setSevenSegmentDisplay(unsigned char * digits);
	
        //! Makes the necessary calculations for determining the odometery of the Roomba using the encoder counts
        void calculateOdometry();
        //! Set the odometry
        /*!
        *  Set the odometry to a determined state.
        *
        *  \param x     The new value for x
        *  \param y     The new value for y
        *  \param yaw   The new value for yaw
        */
        void setOdometry(double x, double y, double yaw);
        //! Reset the odometry
        void resetOdometry(){setOdometry(0.0, 0.0, 0.0);}

		//! Current operation mode, one of ROOMBA_MODE_'s
		unsigned char OImode_;
	
		//! Roomba odometry x
		double odometry_x_;
		//! Roomba odometry y
		double odometry_y_;
		//! Roomba odometry yaw
		double odometry_yaw_;
	
		bool wall_;						//! Wall detected.
		bool virtual_wall_;				//! Virtual wall detected.
		bool cliff_[4];					//! Cliff sensors. Indexes: LEFT FRONT_LEFT FRONT_RIGHT RIGHT
		bool bumper_[2];				//! Bumper sensors. Indexes: LEFT RIGHT
		bool ir_bumper_[6];				//! IR bumper sensors. Indexes: LEFT FRONT_LEFT CENTER_LEFT CENTER_RIGHT FRONT_RIGHT RIGHT
		bool wheel_drop_[2];			//! Wheel drop sensors: Indexes: LEFT RIGHT
		int wall_signal_;				//! Wall signal.
		int cliff_signal_[4];			//! CLiff sensors signal. Indexes: LEFT FRONT_LEFT FRONT_RIGHT RIGHT
		int ir_bumper_signal_[6];		//! IR bumper sensors signal. Indexes: LEFT FRONT_LEFT CENTER_LEFT CENTER_RIGHT FRONT_RIGHT RIGHT
		unsigned char ir_char_[3];		//! IR characters received. Indexes: OMNI LEFT RIGHT
	
        bool button_[8];				//! Buttons. Indexes: BUTTON_CLOCK BUTTON_SCHEDULE BUTTON_DAY BUTTON_HOUR BUTTON_MINUTE BUTTON_DOCK BUTTON_SPOT BUTTON_CLEAN
	
		unsigned char dirt_detect_;		//! Dirt detected
	
		int motor_current_[4];			//! Motor current. Indexes: LEFT RIGHT MAIN_BRUSH SIDE_BRUSH
		bool overcurrent_[4];			//! Motor overcurrent. Indexes: LEFT RIGHT MAIN_BRUSH SIDE_BRUSH
	
		unsigned char charging_state_;	//! One of OI_CHARGING_'s
		bool power_cord_;				//! Whether the Roomba is connected to the power cord or not.
		bool dock_;						//! Whether the Roomba is docked or not.
		float voltage_;					//! Battery voltage in volts.
		float current_;					//! Battery current in amps.
		char temperature_;				//! Battery temperature in C degrees.
		float charge_;					//! Battery charge in Ah.
		float capacity_;				//! Battery capacity in Ah
	
		int stasis_;					//! 1 when the robot is going forward, 0 otherwise

        int distance_;                  //! Amount of distance travelled since last reading. Not being used, poor resolution.
        int angle_;                     //! Amount of angle turned since last reading. Not being used, poor resolution.

        // Flags
        bool cliff_flag_[4];
        bool bumper_flag_[2];
        bool ir_bumper_flag_[6];
        bool wheel_drop_flag_[2];
        bool ir_char_flag_[3];
        bool button_flag_[8];

		private:
	
		//! Start OI
		/*!
		*  Start the OI, change to roomba to a OImode that allows control.
		*
		*  \param full_control    Whether to set the Roomba on OImode full or not.
		*
        *  \return true if successful, false otherwise
		*/
        bool startOI(bool full_control);
		//! Send OP code
		/*!
		*  Send an OP code to Roomba.
		*
		*  \param code  			OP code to send.
		*
        *  \return true if successful, false otherwise
		*/
        bool sendOpcode(OIOpcode code);

        //! Parse sensor packets
        /*!
        *  Parses the sensor packets coming from the Roomba.
        *
        *  \param buffer        The buffer containning the data to be parsed
        *
        *  \return true if successful, false otherwise
        */
        bool parseSensorPackets(unsigned char * buffer);

        //! Parser helper to set the flags if a sensor state changes.
        template <typename T>
        inline bool checkAndSet(T &value, T new_value)
        {
            bool result = (value == new_value);
            value = new_value;
            return result;
        }

        //! Parser helper function for converting bytes to singed ints.
        inline int buffer2signed_int(unsigned char * buffer, int index)
        {
            int16_t signed_int;

            memcpy(&signed_int, buffer+index, 2);
            signed_int = ntohs(signed_int);

            return (int)signed_int;
        }
        //! Parser helper function for converting bytes to unsinged ints.
        inline int buffer2unsigned_int(unsigned char * buffer, int index)
        {
            uint16_t unsigned_int;

            memcpy(&unsigned_int, buffer+index, 2);
            unsigned_int = ntohs(unsigned_int);

            return (int)unsigned_int;
        }

		//! Cereal port object
		cereal::CerealPort * serial_port_;
		
        //! Set for requesting packets.
        std::set<OIPacketID> request_packets_;
        //! Set for parsing the replied packets. The difference is that the request set admits groups, the reply set does not.
        std::set<OIPacketID> reply_packets_;
        //! The buffer size in the reply.
        unsigned int reply_packets_size_;
        //! Map containning the size in bytes of each packet ID.
        std::map<OIPacketID, unsigned int> packet_size_;

        //! Encoder counts.
        int encoder_counts_[2];
        //! Last encoder counts reading.
        int last_encoder_counts_[2];

        unsigned char clean_color_;
        unsigned char clean_brightness_;
        bool leds_[17];

        bool brush_[3];
        bool brush_direction_[2];
        unsigned char brush_pwm_[3];
	};

}

// EOF
