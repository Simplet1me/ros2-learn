# generated from rosidl_generator_py/resource/_idl.py.em
# with input from base_interface:msg/Example.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Example(type):
    """Metaclass of message 'Example'."""

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
            module = import_type_support('base_interface')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'base_interface.msg.Example')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__example
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__example
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__example
            cls._TYPE_SUPPORT = module.type_support_msg__msg__example
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__example

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Example(metaclass=Metaclass_Example):
    """Message class 'Example'."""

    __slots__ = [
        '_name',
        '_money',
        '_coop_rank',
        '_damage',
    ]

    _fields_and_field_types = {
        'name': 'string',
        'money': 'int32',
        'coop_rank': 'int32',
        'damage': 'int32',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.name = kwargs.get('name', str())
        self.money = kwargs.get('money', int())
        self.coop_rank = kwargs.get('coop_rank', int())
        self.damage = kwargs.get('damage', int())

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
        if self.name != other.name:
            return False
        if self.money != other.money:
            return False
        if self.coop_rank != other.coop_rank:
            return False
        if self.damage != other.damage:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def name(self):
        """Message field 'name'."""
        return self._name

    @name.setter
    def name(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'name' field must be of type 'str'"
        self._name = value

    @builtins.property
    def money(self):
        """Message field 'money'."""
        return self._money

    @money.setter
    def money(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'money' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'money' field must be an integer in [-2147483648, 2147483647]"
        self._money = value

    @builtins.property
    def coop_rank(self):
        """Message field 'coop_rank'."""
        return self._coop_rank

    @coop_rank.setter
    def coop_rank(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'coop_rank' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'coop_rank' field must be an integer in [-2147483648, 2147483647]"
        self._coop_rank = value

    @builtins.property
    def damage(self):
        """Message field 'damage'."""
        return self._damage

    @damage.setter
    def damage(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'damage' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'damage' field must be an integer in [-2147483648, 2147483647]"
        self._damage = value
