# generated from rosidl_generator_py/resource/_idl.py.em
# with input from benchmark_msg:msg/BenchmarkParams.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_BenchmarkParams(type):
    """Metaclass of message 'BenchmarkParams'."""

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
            module = import_type_support('benchmark_msg')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'benchmark_msg.msg.BenchmarkParams')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__benchmark_params
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__benchmark_params
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__benchmark_params
            cls._TYPE_SUPPORT = module.type_support_msg__msg__benchmark_params
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__benchmark_params

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class BenchmarkParams(metaclass=Metaclass_BenchmarkParams):
    """Message class 'BenchmarkParams'."""

    __slots__ = [
        '_enable_adaptative',
        '_full_payload',
        '_mu',
        '_mu_zone1',
        '_mu_zone2',
        '_mu_zone3',
        '_new_vel_max',
        '_new_w_max',
        '_dist_obst',
    ]

    _fields_and_field_types = {
        'enable_adaptative': 'boolean',
        'full_payload': 'boolean',
        'mu': 'double',
        'mu_zone1': 'double',
        'mu_zone2': 'double',
        'mu_zone3': 'double',
        'new_vel_max': 'double',
        'new_w_max': 'double',
        'dist_obst': 'double',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.enable_adaptative = kwargs.get('enable_adaptative', bool())
        self.full_payload = kwargs.get('full_payload', bool())
        self.mu = kwargs.get('mu', float())
        self.mu_zone1 = kwargs.get('mu_zone1', float())
        self.mu_zone2 = kwargs.get('mu_zone2', float())
        self.mu_zone3 = kwargs.get('mu_zone3', float())
        self.new_vel_max = kwargs.get('new_vel_max', float())
        self.new_w_max = kwargs.get('new_w_max', float())
        self.dist_obst = kwargs.get('dist_obst', float())

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
        if self.enable_adaptative != other.enable_adaptative:
            return False
        if self.full_payload != other.full_payload:
            return False
        if self.mu != other.mu:
            return False
        if self.mu_zone1 != other.mu_zone1:
            return False
        if self.mu_zone2 != other.mu_zone2:
            return False
        if self.mu_zone3 != other.mu_zone3:
            return False
        if self.new_vel_max != other.new_vel_max:
            return False
        if self.new_w_max != other.new_w_max:
            return False
        if self.dist_obst != other.dist_obst:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def enable_adaptative(self):
        """Message field 'enable_adaptative'."""
        return self._enable_adaptative

    @enable_adaptative.setter
    def enable_adaptative(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'enable_adaptative' field must be of type 'bool'"
        self._enable_adaptative = value

    @builtins.property
    def full_payload(self):
        """Message field 'full_payload'."""
        return self._full_payload

    @full_payload.setter
    def full_payload(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'full_payload' field must be of type 'bool'"
        self._full_payload = value

    @builtins.property
    def mu(self):
        """Message field 'mu'."""
        return self._mu

    @mu.setter
    def mu(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'mu' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'mu' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._mu = value

    @builtins.property
    def mu_zone1(self):
        """Message field 'mu_zone1'."""
        return self._mu_zone1

    @mu_zone1.setter
    def mu_zone1(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'mu_zone1' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'mu_zone1' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._mu_zone1 = value

    @builtins.property
    def mu_zone2(self):
        """Message field 'mu_zone2'."""
        return self._mu_zone2

    @mu_zone2.setter
    def mu_zone2(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'mu_zone2' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'mu_zone2' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._mu_zone2 = value

    @builtins.property
    def mu_zone3(self):
        """Message field 'mu_zone3'."""
        return self._mu_zone3

    @mu_zone3.setter
    def mu_zone3(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'mu_zone3' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'mu_zone3' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._mu_zone3 = value

    @builtins.property
    def new_vel_max(self):
        """Message field 'new_vel_max'."""
        return self._new_vel_max

    @new_vel_max.setter
    def new_vel_max(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'new_vel_max' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'new_vel_max' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._new_vel_max = value

    @builtins.property
    def new_w_max(self):
        """Message field 'new_w_max'."""
        return self._new_w_max

    @new_w_max.setter
    def new_w_max(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'new_w_max' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'new_w_max' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._new_w_max = value

    @builtins.property
    def dist_obst(self):
        """Message field 'dist_obst'."""
        return self._dist_obst

    @dist_obst.setter
    def dist_obst(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'dist_obst' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'dist_obst' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._dist_obst = value
