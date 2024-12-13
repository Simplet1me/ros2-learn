# generated from rosidl_generator_py/resource/_idl.py.em
# with input from base_interfaces:srv/Recharge.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Recharge_Request(type):
    """Metaclass of message 'Recharge_Request'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('base_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'base_interfaces.srv.Recharge_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__recharge__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__recharge__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__recharge__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__recharge__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__recharge__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Recharge_Request(metaclass=Metaclass_Recharge_Request):
    """Message class 'Recharge_Request'."""

    __slots__ = [
        '_user_name',
        '_user_recharge_amount',
    ]

    _fields_and_field_types = {
        'user_name': 'string',
        'user_recharge_amount': 'int32',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.user_name = kwargs.get('user_name', str())
        self.user_recharge_amount = kwargs.get('user_recharge_amount', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.user_name != other.user_name:
            return False
        if self.user_recharge_amount != other.user_recharge_amount:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def user_name(self):
        """Message field 'user_name'."""
        return self._user_name

    @user_name.setter
    def user_name(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'user_name' field must be of type 'str'"
        self._user_name = value

    @builtins.property
    def user_recharge_amount(self):
        """Message field 'user_recharge_amount'."""
        return self._user_recharge_amount

    @user_recharge_amount.setter
    def user_recharge_amount(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'user_recharge_amount' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'user_recharge_amount' field must be an integer in [-2147483648, 2147483647]"
        self._user_recharge_amount = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_Recharge_Response(type):
    """Metaclass of message 'Recharge_Response'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('base_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'base_interfaces.srv.Recharge_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__recharge__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__recharge__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__recharge__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__recharge__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__recharge__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Recharge_Response(metaclass=Metaclass_Recharge_Response):
    """Message class 'Recharge_Response'."""

    __slots__ = [
        '_user_vip_level',
        '_user_points',
    ]

    _fields_and_field_types = {
        'user_vip_level': 'string',
        'user_points': 'int32',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.user_vip_level = kwargs.get('user_vip_level', str())
        self.user_points = kwargs.get('user_points', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.user_vip_level != other.user_vip_level:
            return False
        if self.user_points != other.user_points:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def user_vip_level(self):
        """Message field 'user_vip_level'."""
        return self._user_vip_level

    @user_vip_level.setter
    def user_vip_level(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'user_vip_level' field must be of type 'str'"
        self._user_vip_level = value

    @builtins.property
    def user_points(self):
        """Message field 'user_points'."""
        return self._user_points

    @user_points.setter
    def user_points(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'user_points' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'user_points' field must be an integer in [-2147483648, 2147483647]"
        self._user_points = value


class Metaclass_Recharge(type):
    """Metaclass of service 'Recharge'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('base_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'base_interfaces.srv.Recharge')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__recharge

            from base_interfaces.srv import _recharge
            if _recharge.Metaclass_Recharge_Request._TYPE_SUPPORT is None:
                _recharge.Metaclass_Recharge_Request.__import_type_support__()
            if _recharge.Metaclass_Recharge_Response._TYPE_SUPPORT is None:
                _recharge.Metaclass_Recharge_Response.__import_type_support__()


class Recharge(metaclass=Metaclass_Recharge):
    from base_interfaces.srv._recharge import Recharge_Request as Request
    from base_interfaces.srv._recharge import Recharge_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
