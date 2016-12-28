; Auto-generated. Do not edit!


(cl:in-package ca_msgs-msg)


;//! \htmlinclude ChargingState.msg.html

(cl:defclass <ChargingState> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (state
    :reader state
    :initarg :state
    :type cl:fixnum
    :initform 0))
)

(cl:defclass ChargingState (<ChargingState>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ChargingState>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ChargingState)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ca_msgs-msg:<ChargingState> is deprecated: use ca_msgs-msg:ChargingState instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <ChargingState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ca_msgs-msg:header-val is deprecated.  Use ca_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'state-val :lambda-list '(m))
(cl:defmethod state-val ((m <ChargingState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ca_msgs-msg:state-val is deprecated.  Use ca_msgs-msg:state instead.")
  (state m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<ChargingState>)))
    "Constants for message type '<ChargingState>"
  '((:CHARGE_NONE . 0)
    (:CHARGE_RECONDITION . 1)
    (:CHARGE_FULL . 2)
    (:CHARGE_TRICKLE . 3)
    (:CHARGE_WAITING . 4)
    (:CHARGE_FAULT . 5))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'ChargingState)))
    "Constants for message type 'ChargingState"
  '((:CHARGE_NONE . 0)
    (:CHARGE_RECONDITION . 1)
    (:CHARGE_FULL . 2)
    (:CHARGE_TRICKLE . 3)
    (:CHARGE_WAITING . 4)
    (:CHARGE_FAULT . 5))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ChargingState>) ostream)
  "Serializes a message object of type '<ChargingState>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'state)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ChargingState>) istream)
  "Deserializes a message object of type '<ChargingState>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'state)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ChargingState>)))
  "Returns string type for a message object of type '<ChargingState>"
  "ca_msgs/ChargingState")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ChargingState)))
  "Returns string type for a message object of type 'ChargingState"
  "ca_msgs/ChargingState")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ChargingState>)))
  "Returns md5sum for a message object of type '<ChargingState>"
  "e4da1ef814a2def80691224a5e5883ea")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ChargingState)))
  "Returns md5sum for a message object of type 'ChargingState"
  "e4da1ef814a2def80691224a5e5883ea")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ChargingState>)))
  "Returns full string definition for message of type '<ChargingState>"
  (cl:format cl:nil "uint8 CHARGE_NONE=0~%uint8 CHARGE_RECONDITION=1~%uint8 CHARGE_FULL=2~%uint8 CHARGE_TRICKLE=3~%uint8 CHARGE_WAITING=4~%uint8 CHARGE_FAULT=5~%~%Header header~%uint8 state~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ChargingState)))
  "Returns full string definition for message of type 'ChargingState"
  (cl:format cl:nil "uint8 CHARGE_NONE=0~%uint8 CHARGE_RECONDITION=1~%uint8 CHARGE_FULL=2~%uint8 CHARGE_TRICKLE=3~%uint8 CHARGE_WAITING=4~%uint8 CHARGE_FAULT=5~%~%Header header~%uint8 state~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ChargingState>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ChargingState>))
  "Converts a ROS message object to a list"
  (cl:list 'ChargingState
    (cl:cons ':header (header msg))
    (cl:cons ':state (state msg))
))
