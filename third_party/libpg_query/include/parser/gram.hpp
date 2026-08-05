/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_BASE_YY_THIRD_PARTY_LIBPG_QUERY_GRAMMAR_GRAMMAR_OUT_HPP_INCLUDED
# define YY_BASE_YY_THIRD_PARTY_LIBPG_QUERY_GRAMMAR_GRAMMAR_OUT_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int base_yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENT = 258,                   /* IDENT  */
    FCONST = 259,                  /* FCONST  */
    SCONST = 260,                  /* SCONST  */
    BCONST = 261,                  /* BCONST  */
    XCONST = 262,                  /* XCONST  */
    Op = 263,                      /* Op  */
    ICONST = 264,                  /* ICONST  */
    PARAM = 265,                   /* PARAM  */
    TYPECAST = 266,                /* TYPECAST  */
    DOT_DOT = 267,                 /* DOT_DOT  */
    COLON_EQUALS = 268,            /* COLON_EQUALS  */
    EQUALS_GREATER = 269,          /* EQUALS_GREATER  */
    INTEGER_DIVISION = 270,        /* INTEGER_DIVISION  */
    POWER_OF = 271,                /* POWER_OF  */
    SINGLE_ARROW = 272,            /* SINGLE_ARROW  */
    DOUBLE_ARROW = 273,            /* DOUBLE_ARROW  */
    SINGLE_COLON = 274,            /* SINGLE_COLON  */
    LESS_EQUALS = 275,             /* LESS_EQUALS  */
    GREATER_EQUALS = 276,          /* GREATER_EQUALS  */
    NOT_EQUALS = 277,              /* NOT_EQUALS  */
    ABORT_P = 278,                 /* ABORT_P  */
    ABSOLUTE_P = 279,              /* ABSOLUTE_P  */
    ACCESS = 280,                  /* ACCESS  */
    ACTION = 281,                  /* ACTION  */
    ADD_P = 282,                   /* ADD_P  */
    ADMIN = 283,                   /* ADMIN  */
    AFTER = 284,                   /* AFTER  */
    AGGREGATE = 285,               /* AGGREGATE  */
    ALL = 286,                     /* ALL  */
    ALSO = 287,                    /* ALSO  */
    ALTER = 288,                   /* ALTER  */
    ALWAYS = 289,                  /* ALWAYS  */
    ANALYSE = 290,                 /* ANALYSE  */
    ANALYZE = 291,                 /* ANALYZE  */
    AND = 292,                     /* AND  */
    ANTI = 293,                    /* ANTI  */
    ANY = 294,                     /* ANY  */
    ARRAY = 295,                   /* ARRAY  */
    AS = 296,                      /* AS  */
    ASC_P = 297,                   /* ASC_P  */
    ASOF = 298,                    /* ASOF  */
    ASSERTION = 299,               /* ASSERTION  */
    ASSIGNMENT = 300,              /* ASSIGNMENT  */
    ASYMMETRIC = 301,              /* ASYMMETRIC  */
    AT = 302,                      /* AT  */
    ATTACH = 303,                  /* ATTACH  */
    ATTRIBUTE = 304,               /* ATTRIBUTE  */
    AUTHORIZATION = 305,           /* AUTHORIZATION  */
    BACKWARD = 306,                /* BACKWARD  */
    BEFORE = 307,                  /* BEFORE  */
    BEGIN_P = 308,                 /* BEGIN_P  */
    BETWEEN = 309,                 /* BETWEEN  */
    BIGINT = 310,                  /* BIGINT  */
    BINARY = 311,                  /* BINARY  */
    BIT = 312,                     /* BIT  */
    BOOLEAN_P = 313,               /* BOOLEAN_P  */
    BOTH = 314,                    /* BOTH  */
    BY = 315,                      /* BY  */
    CACHE = 316,                   /* CACHE  */
    CALL_P = 317,                  /* CALL_P  */
    CALLED = 318,                  /* CALLED  */
    CASCADE = 319,                 /* CASCADE  */
    CASCADED = 320,                /* CASCADED  */
    CASE = 321,                    /* CASE  */
    CAST = 322,                    /* CAST  */
    CATALOG_P = 323,               /* CATALOG_P  */
    CENTURIES_P = 324,             /* CENTURIES_P  */
    CENTURY_P = 325,               /* CENTURY_P  */
    CHAIN = 326,                   /* CHAIN  */
    CHAR_P = 327,                  /* CHAR_P  */
    CHARACTER = 328,               /* CHARACTER  */
    CHARACTERISTICS = 329,         /* CHARACTERISTICS  */
    CHECK_P = 330,                 /* CHECK_P  */
    CHECKPOINT = 331,              /* CHECKPOINT  */
    CLASS = 332,                   /* CLASS  */
    CLOSE = 333,                   /* CLOSE  */
    CLUSTER = 334,                 /* CLUSTER  */
    COALESCE = 335,                /* COALESCE  */
    COLLATE = 336,                 /* COLLATE  */
    COLLATION = 337,               /* COLLATION  */
    COLUMN = 338,                  /* COLUMN  */
    COLUMNS = 339,                 /* COLUMNS  */
    COMMENT = 340,                 /* COMMENT  */
    COMMENTS = 341,                /* COMMENTS  */
    COMMIT = 342,                  /* COMMIT  */
    COMMITTED = 343,               /* COMMITTED  */
    COMPACT = 344,                 /* COMPACT  */
    COMPRESSION = 345,             /* COMPRESSION  */
    CONCURRENTLY = 346,            /* CONCURRENTLY  */
    CONFIGURATION = 347,           /* CONFIGURATION  */
    CONFLICT = 348,                /* CONFLICT  */
    CONNECTION = 349,              /* CONNECTION  */
    CONSTRAINT = 350,              /* CONSTRAINT  */
    CONSTRAINTS = 351,             /* CONSTRAINTS  */
    CONTENT_P = 352,               /* CONTENT_P  */
    CONTINUE_P = 353,              /* CONTINUE_P  */
    CONVERSION_P = 354,            /* CONVERSION_P  */
    COPY = 355,                    /* COPY  */
    COST = 356,                    /* COST  */
    CREATE_P = 357,                /* CREATE_P  */
    CROSS = 358,                   /* CROSS  */
    CSV = 359,                     /* CSV  */
    CUBE = 360,                    /* CUBE  */
    CURRENT_P = 361,               /* CURRENT_P  */
    CURSOR = 362,                  /* CURSOR  */
    CYCLE = 363,                   /* CYCLE  */
    DATA_P = 364,                  /* DATA_P  */
    DATABASE = 365,                /* DATABASE  */
    DAY_P = 366,                   /* DAY_P  */
    DAYS_P = 367,                  /* DAYS_P  */
    DEALLOCATE = 368,              /* DEALLOCATE  */
    DEC = 369,                     /* DEC  */
    DECADE_P = 370,                /* DECADE_P  */
    DECADES_P = 371,               /* DECADES_P  */
    DECIMAL_P = 372,               /* DECIMAL_P  */
    DECLARE = 373,                 /* DECLARE  */
    DEFAULT = 374,                 /* DEFAULT  */
    DEFAULTS = 375,                /* DEFAULTS  */
    DEFERRABLE = 376,              /* DEFERRABLE  */
    DEFERRED = 377,                /* DEFERRED  */
    DEFINER = 378,                 /* DEFINER  */
    DELETE_P = 379,                /* DELETE_P  */
    DELIMITER = 380,               /* DELIMITER  */
    DELIMITERS = 381,              /* DELIMITERS  */
    DEPENDS = 382,                 /* DEPENDS  */
    DESC_P = 383,                  /* DESC_P  */
    DESCRIBE = 384,                /* DESCRIBE  */
    DETACH = 385,                  /* DETACH  */
    DICTIONARY = 386,              /* DICTIONARY  */
    DISABLE_P = 387,               /* DISABLE_P  */
    DISCARD = 388,                 /* DISCARD  */
    DISTINCT = 389,                /* DISTINCT  */
    DO = 390,                      /* DO  */
    DOCUMENT_P = 391,              /* DOCUMENT_P  */
    DOMAIN_P = 392,                /* DOMAIN_P  */
    DOUBLE_P = 393,                /* DOUBLE_P  */
    DROP = 394,                    /* DROP  */
    EACH = 395,                    /* EACH  */
    ELSE = 396,                    /* ELSE  */
    ENABLE_P = 397,                /* ENABLE_P  */
    ENCODING = 398,                /* ENCODING  */
    ENCRYPTED = 399,               /* ENCRYPTED  */
    END_P = 400,                   /* END_P  */
    ENUM_P = 401,                  /* ENUM_P  */
    ERROR_P = 402,                 /* ERROR_P  */
    ESCAPE = 403,                  /* ESCAPE  */
    EVENT = 404,                   /* EVENT  */
    EXCEPT = 405,                  /* EXCEPT  */
    EXCLUDE = 406,                 /* EXCLUDE  */
    EXCLUDING = 407,               /* EXCLUDING  */
    EXCLUSIVE = 408,               /* EXCLUSIVE  */
    EXECUTE = 409,                 /* EXECUTE  */
    EXISTS = 410,                  /* EXISTS  */
    EXPLAIN = 411,                 /* EXPLAIN  */
    EXPORT_P = 412,                /* EXPORT_P  */
    EXPORT_STATE = 413,            /* EXPORT_STATE  */
    EXTENSION = 414,               /* EXTENSION  */
    EXTENSIONS = 415,              /* EXTENSIONS  */
    EXTERNAL = 416,                /* EXTERNAL  */
    EXTRACT = 417,                 /* EXTRACT  */
    FALSE_P = 418,                 /* FALSE_P  */
    FAMILY = 419,                  /* FAMILY  */
    FETCH = 420,                   /* FETCH  */
    FILTER = 421,                  /* FILTER  */
    FINAL = 422,                   /* FINAL  */
    FIRST_P = 423,                 /* FIRST_P  */
    FLOAT_P = 424,                 /* FLOAT_P  */
    FOLLOWING = 425,               /* FOLLOWING  */
    FOR = 426,                     /* FOR  */
    FORCE = 427,                   /* FORCE  */
    FOREIGN = 428,                 /* FOREIGN  */
    FORWARD = 429,                 /* FORWARD  */
    FREEZE = 430,                  /* FREEZE  */
    FROM = 431,                    /* FROM  */
    FULL = 432,                    /* FULL  */
    FUNCTION = 433,                /* FUNCTION  */
    FUNCTIONS = 434,               /* FUNCTIONS  */
    GENERATED = 435,               /* GENERATED  */
    GLOB = 436,                    /* GLOB  */
    GLOBAL = 437,                  /* GLOBAL  */
    GRANT = 438,                   /* GRANT  */
    GRANTED = 439,                 /* GRANTED  */
    GROUP_P = 440,                 /* GROUP_P  */
    GROUPING = 441,                /* GROUPING  */
    GROUPING_ID = 442,             /* GROUPING_ID  */
    GROUPS = 443,                  /* GROUPS  */
    HANDLER = 444,                 /* HANDLER  */
    HAVING = 445,                  /* HAVING  */
    HEADER_P = 446,                /* HEADER_P  */
    HOLD = 447,                    /* HOLD  */
    HOUR_P = 448,                  /* HOUR_P  */
    HOURS_P = 449,                 /* HOURS_P  */
    IDENTITY_P = 450,              /* IDENTITY_P  */
    IF_P = 451,                    /* IF_P  */
    IGNORE_P = 452,                /* IGNORE_P  */
    ILIKE = 453,                   /* ILIKE  */
    IMMEDIATE = 454,               /* IMMEDIATE  */
    IMMUTABLE = 455,               /* IMMUTABLE  */
    IMPLICIT_P = 456,              /* IMPLICIT_P  */
    IMPORT_P = 457,                /* IMPORT_P  */
    IN_P = 458,                    /* IN_P  */
    INCLUDE_P = 459,               /* INCLUDE_P  */
    INCLUDING = 460,               /* INCLUDING  */
    INCREMENT = 461,               /* INCREMENT  */
    INDEX = 462,                   /* INDEX  */
    INDEXES = 463,                 /* INDEXES  */
    INHERIT = 464,                 /* INHERIT  */
    INHERITS = 465,                /* INHERITS  */
    INITIALLY = 466,               /* INITIALLY  */
    INLINE_P = 467,                /* INLINE_P  */
    INNER_P = 468,                 /* INNER_P  */
    INOUT = 469,                   /* INOUT  */
    INPUT_P = 470,                 /* INPUT_P  */
    INSENSITIVE = 471,             /* INSENSITIVE  */
    INSERT = 472,                  /* INSERT  */
    INSTALL = 473,                 /* INSTALL  */
    INSTEAD = 474,                 /* INSTEAD  */
    INT_P = 475,                   /* INT_P  */
    INTEGER = 476,                 /* INTEGER  */
    INTERSECT = 477,               /* INTERSECT  */
    INTERVAL = 478,                /* INTERVAL  */
    INTO = 479,                    /* INTO  */
    INVOKER = 480,                 /* INVOKER  */
    IS = 481,                      /* IS  */
    ISNULL = 482,                  /* ISNULL  */
    ISOLATION = 483,               /* ISOLATION  */
    JOIN = 484,                    /* JOIN  */
    JSON = 485,                    /* JSON  */
    KEY = 486,                     /* KEY  */
    LABEL = 487,                   /* LABEL  */
    LAMBDA = 488,                  /* LAMBDA  */
    LANGUAGE = 489,                /* LANGUAGE  */
    LARGE_P = 490,                 /* LARGE_P  */
    LAST_P = 491,                  /* LAST_P  */
    LATERAL_P = 492,               /* LATERAL_P  */
    LEADING = 493,                 /* LEADING  */
    LEAKPROOF = 494,               /* LEAKPROOF  */
    LEFT = 495,                    /* LEFT  */
    LEVEL = 496,                   /* LEVEL  */
    LIKE = 497,                    /* LIKE  */
    LIMIT = 498,                   /* LIMIT  */
    LISTEN = 499,                  /* LISTEN  */
    LOAD = 500,                    /* LOAD  */
    LOCAL = 501,                   /* LOCAL  */
    LOCATION = 502,                /* LOCATION  */
    LOCK_P = 503,                  /* LOCK_P  */
    LOCKED = 504,                  /* LOCKED  */
    LOGGED = 505,                  /* LOGGED  */
    MACRO = 506,                   /* MACRO  */
    MAP = 507,                     /* MAP  */
    MAPPING = 508,                 /* MAPPING  */
    MATCH = 509,                   /* MATCH  */
    MATCHED = 510,                 /* MATCHED  */
    MATERIALIZED = 511,            /* MATERIALIZED  */
    MAXVALUE = 512,                /* MAXVALUE  */
    MERGE = 513,                   /* MERGE  */
    METHOD = 514,                  /* METHOD  */
    MICROSECOND_P = 515,           /* MICROSECOND_P  */
    MICROSECONDS_P = 516,          /* MICROSECONDS_P  */
    MILLENNIA_P = 517,             /* MILLENNIA_P  */
    MILLENNIUM_P = 518,            /* MILLENNIUM_P  */
    MILLISECOND_P = 519,           /* MILLISECOND_P  */
    MILLISECONDS_P = 520,          /* MILLISECONDS_P  */
    MINUTE_P = 521,                /* MINUTE_P  */
    MINUTES_P = 522,               /* MINUTES_P  */
    MINVALUE = 523,                /* MINVALUE  */
    MODE = 524,                    /* MODE  */
    MONTH_P = 525,                 /* MONTH_P  */
    MONTHS_P = 526,                /* MONTHS_P  */
    MOVE = 527,                    /* MOVE  */
    NAME_P = 528,                  /* NAME_P  */
    NAMES = 529,                   /* NAMES  */
    NATIONAL = 530,                /* NATIONAL  */
    NATURAL = 531,                 /* NATURAL  */
    NCHAR = 532,                   /* NCHAR  */
    NEW = 533,                     /* NEW  */
    NEXT = 534,                    /* NEXT  */
    NO = 535,                      /* NO  */
    NONE = 536,                    /* NONE  */
    NOT = 537,                     /* NOT  */
    NOTHING = 538,                 /* NOTHING  */
    NOTIFY = 539,                  /* NOTIFY  */
    NOTNULL = 540,                 /* NOTNULL  */
    NOWAIT = 541,                  /* NOWAIT  */
    NULL_P = 542,                  /* NULL_P  */
    NULLIF = 543,                  /* NULLIF  */
    NULLS_P = 544,                 /* NULLS_P  */
    NUMERIC = 545,                 /* NUMERIC  */
    OBJECT_P = 546,                /* OBJECT_P  */
    OF = 547,                      /* OF  */
    OFF = 548,                     /* OFF  */
    OFFSET = 549,                  /* OFFSET  */
    OIDS = 550,                    /* OIDS  */
    OLD = 551,                     /* OLD  */
    ON = 552,                      /* ON  */
    ONLY = 553,                    /* ONLY  */
    OPERATOR = 554,                /* OPERATOR  */
    OPTION = 555,                  /* OPTION  */
    OPTIONS = 556,                 /* OPTIONS  */
    OR = 557,                      /* OR  */
    ORDER = 558,                   /* ORDER  */
    ORDINALITY = 559,              /* ORDINALITY  */
    OTHERS = 560,                  /* OTHERS  */
    OUT_P = 561,                   /* OUT_P  */
    OUTER_P = 562,                 /* OUTER_P  */
    OVER = 563,                    /* OVER  */
    OVERLAPS = 564,                /* OVERLAPS  */
    OVERLAY = 565,                 /* OVERLAY  */
    OVERRIDING = 566,              /* OVERRIDING  */
    OWNED = 567,                   /* OWNED  */
    OWNER = 568,                   /* OWNER  */
    PARALLEL = 569,                /* PARALLEL  */
    PARSER = 570,                  /* PARSER  */
    PARTIAL = 571,                 /* PARTIAL  */
    PARTITION = 572,               /* PARTITION  */
    PARTITIONED = 573,             /* PARTITIONED  */
    PASSING = 574,                 /* PASSING  */
    PASSWORD = 575,                /* PASSWORD  */
    PERCENT = 576,                 /* PERCENT  */
    PERSISTENT = 577,              /* PERSISTENT  */
    PIVOT = 578,                   /* PIVOT  */
    PIVOT_LONGER = 579,            /* PIVOT_LONGER  */
    PIVOT_WIDER = 580,             /* PIVOT_WIDER  */
    PLACING = 581,                 /* PLACING  */
    PLANS = 582,                   /* PLANS  */
    POLICY = 583,                  /* POLICY  */
    POSITION = 584,                /* POSITION  */
    POSITIONAL = 585,              /* POSITIONAL  */
    PRAGMA_P = 586,                /* PRAGMA_P  */
    PRECEDING = 587,               /* PRECEDING  */
    PRECISION = 588,               /* PRECISION  */
    PREPARE = 589,                 /* PREPARE  */
    PREPARED = 590,                /* PREPARED  */
    PRESERVE = 591,                /* PRESERVE  */
    PRIMARY = 592,                 /* PRIMARY  */
    PRIOR = 593,                   /* PRIOR  */
    PRIVILEGES = 594,              /* PRIVILEGES  */
    PROCEDURAL = 595,              /* PROCEDURAL  */
    PROCEDURE = 596,               /* PROCEDURE  */
    PROGRAM = 597,                 /* PROGRAM  */
    PUBLICATION = 598,             /* PUBLICATION  */
    QUALIFY = 599,                 /* QUALIFY  */
    QUARTER_P = 600,               /* QUARTER_P  */
    QUARTERS_P = 601,              /* QUARTERS_P  */
    QUOTE = 602,                   /* QUOTE  */
    RANGE = 603,                   /* RANGE  */
    READ_P = 604,                  /* READ_P  */
    REAL = 605,                    /* REAL  */
    REASSIGN = 606,                /* REASSIGN  */
    RECHECK = 607,                 /* RECHECK  */
    RECURSIVE = 608,               /* RECURSIVE  */
    REF = 609,                     /* REF  */
    REFERENCES = 610,              /* REFERENCES  */
    REFERENCING = 611,             /* REFERENCING  */
    REFRESH = 612,                 /* REFRESH  */
    REINDEX = 613,                 /* REINDEX  */
    RELATIVE_P = 614,              /* RELATIVE_P  */
    RELEASE = 615,                 /* RELEASE  */
    RENAME = 616,                  /* RENAME  */
    REPEATABLE = 617,              /* REPEATABLE  */
    REPLACE = 618,                 /* REPLACE  */
    REPLICA = 619,                 /* REPLICA  */
    RESET = 620,                   /* RESET  */
    RESPECT_P = 621,               /* RESPECT_P  */
    RESTART = 622,                 /* RESTART  */
    RESTRICT = 623,                /* RESTRICT  */
    RETURNING = 624,               /* RETURNING  */
    RETURNS = 625,                 /* RETURNS  */
    REVOKE = 626,                  /* REVOKE  */
    RIGHT = 627,                   /* RIGHT  */
    ROLE = 628,                    /* ROLE  */
    ROLLBACK = 629,                /* ROLLBACK  */
    ROLLUP = 630,                  /* ROLLUP  */
    ROW = 631,                     /* ROW  */
    ROWS = 632,                    /* ROWS  */
    RULE = 633,                    /* RULE  */
    SAMPLE = 634,                  /* SAMPLE  */
    SAVEPOINT = 635,               /* SAVEPOINT  */
    SCHEMA = 636,                  /* SCHEMA  */
    SCHEMAS = 637,                 /* SCHEMAS  */
    SCOPE = 638,                   /* SCOPE  */
    SCROLL = 639,                  /* SCROLL  */
    SEARCH = 640,                  /* SEARCH  */
    SECOND_P = 641,                /* SECOND_P  */
    SECONDS_P = 642,               /* SECONDS_P  */
    SECRET = 643,                  /* SECRET  */
    SECURITY = 644,                /* SECURITY  */
    SELECT = 645,                  /* SELECT  */
    SEMI = 646,                    /* SEMI  */
    SEQUENCE = 647,                /* SEQUENCE  */
    SEQUENCES = 648,               /* SEQUENCES  */
    SERIALIZABLE = 649,            /* SERIALIZABLE  */
    SERVER = 650,                  /* SERVER  */
    SESSION = 651,                 /* SESSION  */
    SET = 652,                     /* SET  */
    SETOF = 653,                   /* SETOF  */
    SETS = 654,                    /* SETS  */
    SHARE = 655,                   /* SHARE  */
    SHOW = 656,                    /* SHOW  */
    SIMILAR = 657,                 /* SIMILAR  */
    SIMPLE = 658,                  /* SIMPLE  */
    SKIP = 659,                    /* SKIP  */
    SMALLINT = 660,                /* SMALLINT  */
    SNAPSHOT = 661,                /* SNAPSHOT  */
    SOME = 662,                    /* SOME  */
    SORTED = 663,                  /* SORTED  */
    SOURCE_P = 664,                /* SOURCE_P  */
    SQL_P = 665,                   /* SQL_P  */
    STABLE = 666,                  /* STABLE  */
    STANDALONE_P = 667,            /* STANDALONE_P  */
    START = 668,                   /* START  */
    STATEMENT = 669,               /* STATEMENT  */
    STATISTICS = 670,              /* STATISTICS  */
    STDIN = 671,                   /* STDIN  */
    STDOUT = 672,                  /* STDOUT  */
    STORAGE = 673,                 /* STORAGE  */
    STORED = 674,                  /* STORED  */
    STRICT_P = 675,                /* STRICT_P  */
    STRIP_P = 676,                 /* STRIP_P  */
    STRUCT = 677,                  /* STRUCT  */
    SUBSCRIPTION = 678,            /* SUBSCRIPTION  */
    SUBSTRING = 679,               /* SUBSTRING  */
    SUMMARIZE = 680,               /* SUMMARIZE  */
    SYMMETRIC = 681,               /* SYMMETRIC  */
    SYSID = 682,                   /* SYSID  */
    SYSTEM_P = 683,                /* SYSTEM_P  */
    TABLE = 684,                   /* TABLE  */
    TABLES = 685,                  /* TABLES  */
    TABLESAMPLE = 686,             /* TABLESAMPLE  */
    TABLESPACE = 687,              /* TABLESPACE  */
    TARGET_P = 688,                /* TARGET_P  */
    TEMP = 689,                    /* TEMP  */
    TEMPLATE = 690,                /* TEMPLATE  */
    TEMPORARY = 691,               /* TEMPORARY  */
    TEXT_P = 692,                  /* TEXT_P  */
    THEN = 693,                    /* THEN  */
    TIES = 694,                    /* TIES  */
    TIME = 695,                    /* TIME  */
    TIMESTAMP = 696,               /* TIMESTAMP  */
    TO = 697,                      /* TO  */
    TRAILING = 698,                /* TRAILING  */
    TRANSACTION = 699,             /* TRANSACTION  */
    TRANSFORM = 700,               /* TRANSFORM  */
    TREAT = 701,                   /* TREAT  */
    TRIGGER = 702,                 /* TRIGGER  */
    TRIM = 703,                    /* TRIM  */
    TRUE_P = 704,                  /* TRUE_P  */
    TRUNCATE = 705,                /* TRUNCATE  */
    TRUSTED = 706,                 /* TRUSTED  */
    TRY_CAST = 707,                /* TRY_CAST  */
    TYPE_P = 708,                  /* TYPE_P  */
    TYPES_P = 709,                 /* TYPES_P  */
    UNBOUNDED = 710,               /* UNBOUNDED  */
    UNCOMMITTED = 711,             /* UNCOMMITTED  */
    UNENCRYPTED = 712,             /* UNENCRYPTED  */
    UNION = 713,                   /* UNION  */
    UNIQUE = 714,                  /* UNIQUE  */
    UNKNOWN = 715,                 /* UNKNOWN  */
    UNLISTEN = 716,                /* UNLISTEN  */
    UNLOGGED = 717,                /* UNLOGGED  */
    UNPACK = 718,                  /* UNPACK  */
    UNPIVOT = 719,                 /* UNPIVOT  */
    UNTIL = 720,                   /* UNTIL  */
    UPDATE = 721,                  /* UPDATE  */
    USE_P = 722,                   /* USE_P  */
    USER = 723,                    /* USER  */
    USING = 724,                   /* USING  */
    VACUUM = 725,                  /* VACUUM  */
    VALID = 726,                   /* VALID  */
    VALIDATE = 727,                /* VALIDATE  */
    VALIDATOR = 728,               /* VALIDATOR  */
    VALUE_P = 729,                 /* VALUE_P  */
    VALUES = 730,                  /* VALUES  */
    VARCHAR = 731,                 /* VARCHAR  */
    VARIABLE_P = 732,              /* VARIABLE_P  */
    VARIADIC = 733,                /* VARIADIC  */
    VARYING = 734,                 /* VARYING  */
    VERBOSE = 735,                 /* VERBOSE  */
    VERSION_P = 736,               /* VERSION_P  */
    VIEW = 737,                    /* VIEW  */
    VIEWS = 738,                   /* VIEWS  */
    VIRTUAL = 739,                 /* VIRTUAL  */
    VOLATILE = 740,                /* VOLATILE  */
    WEEK_P = 741,                  /* WEEK_P  */
    WEEKS_P = 742,                 /* WEEKS_P  */
    WHEN = 743,                    /* WHEN  */
    WHERE = 744,                   /* WHERE  */
    WHITESPACE_P = 745,            /* WHITESPACE_P  */
    WINDOW = 746,                  /* WINDOW  */
    WITH = 747,                    /* WITH  */
    WITHIN = 748,                  /* WITHIN  */
    WITHOUT = 749,                 /* WITHOUT  */
    WORK = 750,                    /* WORK  */
    WRAPPER = 751,                 /* WRAPPER  */
    WRITE_P = 752,                 /* WRITE_P  */
    XML_P = 753,                   /* XML_P  */
    XMLATTRIBUTES = 754,           /* XMLATTRIBUTES  */
    XMLCONCAT = 755,               /* XMLCONCAT  */
    XMLELEMENT = 756,              /* XMLELEMENT  */
    XMLEXISTS = 757,               /* XMLEXISTS  */
    XMLFOREST = 758,               /* XMLFOREST  */
    XMLNAMESPACES = 759,           /* XMLNAMESPACES  */
    XMLPARSE = 760,                /* XMLPARSE  */
    XMLPI = 761,                   /* XMLPI  */
    XMLROOT = 762,                 /* XMLROOT  */
    XMLSERIALIZE = 763,            /* XMLSERIALIZE  */
    XMLTABLE = 764,                /* XMLTABLE  */
    YEAR_P = 765,                  /* YEAR_P  */
    YEARS_P = 766,                 /* YEARS_P  */
    YES_P = 767,                   /* YES_P  */
    ZONE = 768,                    /* ZONE  */
    NOT_LA = 769,                  /* NOT_LA  */
    NULLS_LA = 770,                /* NULLS_LA  */
    WITH_LA = 771,                 /* WITH_LA  */
    POSTFIXOP = 772,               /* POSTFIXOP  */
    UMINUS = 773                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 14 "third_party/libpg_query/grammar/grammar.y"

	core_YYSTYPE		core_yystype;
	/* these fields must match core_YYSTYPE: */
	int					ival;
	char				*str;
	const char			*keyword;
	const char          *conststr;

	char				chr;
	bool				boolean;
	PGJoinType			jtype;
	PGDropBehavior		dbehavior;
	PGOnCommitAction		oncommit;
	PGOnCreateConflict		oncreateconflict;
	PGList				*list;
	PGNode				*node;
	PGValue				*value;
	PGObjectType			objtype;
	PGTypeName			*typnam;
	PGObjectWithArgs		*objwithargs;
	PGDefElem				*defelt;
	PGSortBy				*sortby;
	PGWindowDef			*windef;
	PGJoinExpr			*jexpr;
	PGIndexElem			*ielem;
	PGAlias				*alias;
	PGRangeVar			*range;
	PGIntoClause			*into;
	PGCTEMaterialize			ctematerialize;
	PGWithClause			*with;
	PGInferClause			*infer;
	PGOnConflictClause	*onconflict;
	PGOnConflictActionAlias onconflictshorthand;
	PGAIndices			*aind;
	PGResTarget			*target;
	PGInsertStmt			*istmt;
	PGVariableSetStmt		*vsetstmt;
	PGOverridingKind       override;
	PGSortByDir            sortorder;
	PGSortByNulls          nullorder;
	PGIgnoreNulls          ignorenulls;
	PGConstrType           constr;
	PGLockClauseStrength lockstrength;
	PGLockWaitPolicy lockwaitpolicy;
	PGSubLinkType subquerytype;
	PGViewCheckOption viewcheckoption;
	PGInsertColumnOrder bynameorposition;
	PGLoadInstallType loadinstalltype;
	PGTransactionStmtType transactiontype;
	PGMergeAction mergeaction;

#line 634 "third_party/libpg_query/grammar/grammar_out.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int base_yyparse (core_yyscan_t yyscanner);


#endif /* !YY_BASE_YY_THIRD_PARTY_LIBPG_QUERY_GRAMMAR_GRAMMAR_OUT_HPP_INCLUDED  */
