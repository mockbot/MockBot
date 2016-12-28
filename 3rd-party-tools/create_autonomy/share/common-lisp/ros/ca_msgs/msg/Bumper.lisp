; Auto-generated. Do not edit!


(cl:in-package ca_msgs-msg)


;//! \htmlinclude Bumper.msg.html

(cl:defclass <Bumper> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (is_left_pressed
    :reader is_left_pressed
    :initarg :is_left_pressed
    :type cl:boolean
    :initform cl:nil)
   (is_right_pressed
    :reader is_right_pressed
    :initarg :is_right_pressed
    :type cl:boolean
    :initform cl:nil)
   (is_light_left
    :reader is_light_left
    :initarg :is_light_left
    :type cl:boolean
    :initform cl:nil)
   (is_light_front_left
    :reader is_light_front_left
    :initarg :is_light_front_left
    :type cl:boolean
    :initform cl:nil)
   (is_light_center_left
    :reader is_light_center_left
    :initarg :is_light_center_left
    :type cl:boolean
    :initform cl:nil)
   (is_light_center_right
    :reader is_light_center_right
    :initarg :is_light_center_right
    :type cl:boolean
    :initform cl:nil)
   (is_light_front_right
    :reader is_light_front_right
    :initarg :is_light_front_right
    :type cl:boolean
    :initform cl:nil)
   (is_light_right
    :reader is_light_right
    :initarg :is_light_right
    :type cl:boolean
    :initform cl:nil)
   (light_signal_left
    :reader light_signal_left
    :initarg :light_signal_left
    :type cl:fixnum
    :initform 0)
   (light_signal_front_left
    :reader light_signal_front_left
    :initarg :light_signal_front_left
    :type cl:fixnum
    :initform 0)
   (light_signal_center_left
    :reader light_signal_center_left
    :initarg :light_signal_center_left
    :type cl:fixnum
    :initform 0)
   (light_signal_center_right
    :reader light_signal_center_right
    :initarg :light_signal_center_right
    :type cl:fixnum
    :initform 0)
   (light_signal_front_right
    :reader light_signal_front_right
    :initarg :light_signal_front_right
    :type cl:fixnum
    :initform 0)
   (light_signal_right
    :reader light_signal_right
    :initarg :light_signal_right
    :type cl:fixnum
    :initform 0))
)

(cl:defclass Bumper (<Bumper>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Bumper>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Bumper)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ca_msgs-msg:<Bumper> is deprecated: use ca_msgs-msg:Bumper instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Bumper>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ca_msgs-msg:header-val is deprecated.  Use ca_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'is_left_pressed-val :lambda-list '(m))
(cl:defmethod is_left_pressed-val ((m <Bumper>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ca_msgs-msg:is_left_pressed-val is deprecated.  Use ca_msgs-msg:is_left_pressed instead.")
  (is_left_pressed m))

(cl:ensure-generic-function 'is_right_pressed-val :lambda-list '(m))
(cl:defmethod is_right_pressed-val ((m <Bumper>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ca_msgs-msg:is_right_pressed-val is deprecated.  Use ca_msgs-msg:is_right_pressed instead.")
  (is_right_pressed m))

(cl:ensure-generic-function 'is_light_left-val :lambda-list '(m))
(cl:defmethod is_light_left-val ((m <Bumper>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ca_msgs-msg:is_light_left-val is deprecated.  Use ca_msgs-msg:is_light_left instead.")
  (is_light_left m))

(cl:ensure-generic-function 'is_light_front_left-val :lambda-list '(m))
(cl:defmethod is_light_front_left-val ((m <Bumper>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ca_msgs-msg:is_light_front_left-val is deprecated.  Use ca_msgs-msg:is_light_front_left instead.")
  (is_light_front_left m))

(cl:ensure-generic-function 'is_light_center_left-val :lambda-list '(m))
(cl:defmethod is_light_center_left-val ((m <Bumper>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ca_msgs-msg:is_light_center_left-val is deprecated.  Use ca_msgs-msg:is_light_center_left instead.")
  (is_light_center_left m))

(cl:ensure-generic-function 'is_light_center_right-val :lambda-list '(m))
(cl:defmethod is_light_center_right-val ((m <Bumper>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ca_msgs-msg:is_light_center_right-val is deprecated.  Use ca_msgs-msg:is_light_center_right instead.")
  (is_light_center_right m))

(cl:ensure-generic-function 'is_light_front_right-val :lambda-list '(m))
(cl:defmethod is_light_front_right-val ((m <Bumper>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ca_msgs-msg:is_light_front_right-val is deprecated.  Use ca_msgs-msg:is_light_front_right instead.")
  (is_light_front_right m))

(cl:ensure-generic-function 'is_light_right-val :lambda-list '(m))
(cl:defmethod is_light_right-val ((m <Bumper>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ca_msgs-msg:is_light_right-val is deprecated.  Use ca_msgs-msg:is_light_right instead.")
  (is_light_right m))

(cl:ensure-generic-function 'light_signal_left-val :lambda-list '(m))
(cl:defmethod light_signal_left-val ((m <Bumper>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ca_msgs-msg:light_signal_left-val is deprecated.  Use ca_msgs-msg:light_signal_left instead.")
  (light_signal_left m))

(cl:ensure-generic-function 'light_signal_front_left-val :lambda-list '(m))
(cl:defmethod light_signal_front_left-val ((m <Bumper>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ca_msgs-msg:light_signal_front_left-val is deprecated.  Use ca_msgs-msg:light_signal_front_left instead.")
  (light_signal_front_left m))

(cl:ensure-generic-function 'light_signal_center_left-val :lambda-list '(m))
(cl:defmethod light_signal_center_left-val ((m <Bumper>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ca_msgs-msg:light_signal_center_left-val is deprecated.  Use ca_msgs-msg:light_signal_center_left instead.")
  (light_signal_center_left m))

(cl:ensure-generic-function 'light_signal_center_right-val :lambda-list '(m))
(cl:defmethod light_signal_center_right-val ((m <Bumper>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ca_msgs-msg:light_signal_center_right-val is deprecated.  Use ca_msgs-msg:light_signal_center_right instead.")
  (light_signal_center_right m))

(cl:ensure-generic-function 'light_signal_front_right-val :lambda-list '(m))
(cl:defmethod light_signal_front_right-val ((m <Bumper>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ca_msgs-msg:light_signal_front_right-val is deprecated.  Use ca_msgs-msg:light_signal_front_right instead.")
  (light_signal_front_right m))

(cl:ensure-generic-function 'light_signal_right-val :lambda-list '(m))
(cl:defmethod light_signal_right-val ((m <Bumper>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ca_msgs-msg:light_signal_right-val is deprecated.  Use ca_msgs-msg:light_signal_right instead.")
  (light_signal_right m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Bumper>) ostream)
  "Serializes a message object of type '<Bumper>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'is_left_pressed) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'is_right_pressed) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'is_light_left) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'is_light_front_left) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'is_light_center_left) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'is_light_center_right) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'is_light_front_right) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'is_light_right) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'light_signal_left)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'light_signal_left)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'light_signal_front_left)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'light_signal_front_left)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'light_signal_center_left)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'light_signal_center_left)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'light_signal_center_right)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'light_signal_center_right)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'light_signal_front_right)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'light_signal_front_right)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'light_signal_right)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'light_signal_right)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Bumper>) istream)
  "Deserializes a message object of type '<Bumper>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:slot-value msg 'is_left_pressed) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'is_right_pressed) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'is_light_left) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'is_light_front_left) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'is_light_center_left) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'is_light_center_right) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'is_light_front_right) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'is_light_right) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'light_signal_left)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'light_signal_left)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'light_signal_front_left)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'light_signal_front_left)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'light_signal_center_left)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'light_signal_center_left)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'light_signal_center_right)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'light_signal_center_right)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'light_signal_front_right)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'light_signal_front_right)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'light_signal_right)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'light_signal_right)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Bumper>)))
  "Returns string type for a message object of type '<Bumper>"
  "ca_msgs/Bumper")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Bumper)))
  "Returns string type for a message object of type 'Bumper"
  "ca_msgs/Bumper")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Bumper>)))
  "Returns md5sum for a message object of type '<Bumper>"
  "18fe5b1d31e6a8db180b924157ac665e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Bumper)))
  "Returns md5sum for a message object of type 'Bumper"
  "18fe5b1d31e6a8db180b924157ac665e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Bumper>)))
  "Returns full string definition for message of type '<Bumper>"
  (cl:format cl:nil "Header header~%~%# Contact sensors~%bool is_left_pressed~%bool is_right_pressed~%~%# Bumper light sensors (Create 2 only) in order from left to right~%# Value = true if an obstacle detected~%bool is_light_left~%bool is_light_front_left~%bool is_light_center_left~%bool is_light_center_right~%bool is_light_front_right~%bool is_light_right~%~%# Raw light sensor signals~%# Values in range [0, 4095]~%uint16 light_signal_left~%uint16 light_signal_front_left~%uint16 light_signal_center_left~%uint16 light_signal_center_right~%uint16 light_signal_front_right~%uint16 light_signal_right~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Bumper)))
  "Returns full string definition for message of type 'Bumper"
  (cl:format cl:nil "Header header~%~%# Contact sensors~%bool is_left_pressed~%bool is_right_pressed~%~%# Bumper light sensors (Create 2 only) in order from left to right~%# Value = true if an obstacle detected~%bool is_light_left~%bool is_light_front_left~%bool is_light_center_left~%bool is_light_center_right~%bool is_light_front_right~%bool is_light_right~%~%# Raw light sensor signals~%# Values in range [0, 4095]~%uint16 light_signal_left~%uint16 light_signal_front_left~%uint16 light_signal_center_left~%uint16 light_signal_center_right~%uint16 light_signal_front_right~%uint16 light_signal_right~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Bumper>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     1
     1
     1
     1
     1
     1
     1
     1
     2
     2
     2
     2
     2
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Bumper>))
  "Converts a ROS message object to a list"
  (cl:list 'Bumper
    (cl:cons ':header (header msg))
    (cl:cons ':is_left_pressed (is_left_pressed msg))
    (cl:cons ':is_right_pressed (is_right_pressed msg))
    (cl:cons ':is_light_left (is_light_left msg))
    (cl:cons ':is_light_front_left (is_light_front_left msg))
    (cl:cons ':is_light_center_left (is_light_center_left msg))
    (cl:cons ':is_light_center_right (is_light_center_right msg))
    (cl:cons ':is_light_front_right (is_light_front_right msg))
    (cl:cons ':is_light_right (is_light_right msg))
    (cl:cons ':light_signal_left (light_signal_left msg))
    (cl:cons ':light_signal_front_left (light_signal_front_left msg))
    (cl:cons ':light_signal_center_left (light_signal_center_left msg))
    (cl:cons ':light_signal_center_right (light_signal_center_right msg))
    (cl:cons ':light_signal_front_right (light_signal_front_right msg))
    (cl:cons ':light_signal_right (light_signal_right msg))
))
