/*-------------------------------------------------------------------------
 *
 * int.c
 *		Overflow checks for signed integers
 *
 * Copyright (c) 1996-2019, PostgreSQL Global Development Group
 *
 * IDENTIFICATION
 *		  overflow/int.c
 *
 *-------------------------------------------------------------------------
 */

#include "postgres.h"
#include "fmgr.h"

#include "common/int.h"
#include "common/string.h"
#include "utils/builtins.h"

PG_MODULE_MAGIC;

/* smallint functions */
PG_FUNCTION_INFO_V1(pg_add_int16_overflow);
PG_FUNCTION_INFO_V1(pg_sub_int16_overflow);
PG_FUNCTION_INFO_V1(pg_mul_int16_overflow);

Datum
pg_add_int16_overflow(PG_FUNCTION_ARGS)
{
	int16		v1 = PG_GETARG_INT16(0);
	int16		v2 = PG_GETARG_INT16(1);
	int16		result;

	PG_RETURN_BOOL(pg_add_s16_overflow(v1, v2, &result));
}

Datum
pg_sub_int16_overflow(PG_FUNCTION_ARGS)
{
	int16		v1 = PG_GETARG_INT16(0);
	int16		v2 = PG_GETARG_INT16(1);
	int16		result;

	PG_RETURN_BOOL(pg_sub_s16_overflow(v1, v2, &result));
}

Datum
pg_mul_int16_overflow(PG_FUNCTION_ARGS)
{
	int16		v1 = PG_GETARG_INT16(0);
	int16		v2 = PG_GETARG_INT16(1);
	int16		result;

	PG_RETURN_BOOL(pg_mul_s16_overflow(v1, v2, &result));
}

/* int functions */
PG_FUNCTION_INFO_V1(pg_add_int32_overflow);
PG_FUNCTION_INFO_V1(pg_sub_int32_overflow);
PG_FUNCTION_INFO_V1(pg_mul_int32_overflow);

Datum
pg_add_int32_overflow(PG_FUNCTION_ARGS)
{
	int32		v1 = PG_GETARG_INT32(0);
	int32		v2 = PG_GETARG_INT32(1);
	int32		result;

	PG_RETURN_BOOL(pg_add_s32_overflow(v1, v2, &result));
}

Datum
pg_sub_int32_overflow(PG_FUNCTION_ARGS)
{
	int32		v1 = PG_GETARG_INT32(0);
	int32		v2 = PG_GETARG_INT32(1);
	int32		result;

	PG_RETURN_BOOL(pg_sub_s32_overflow(v1, v2, &result));
}

Datum
pg_mul_int32_overflow(PG_FUNCTION_ARGS)
{
	int32		v1 = PG_GETARG_INT32(0);
	int32		v2 = PG_GETARG_INT32(1);
	int32		result;

	PG_RETURN_BOOL(pg_mul_s32_overflow(v1, v2, &result));
}

/* bigint functions */
PG_FUNCTION_INFO_V1(pg_add_int64_overflow);
PG_FUNCTION_INFO_V1(pg_sub_int64_overflow);
PG_FUNCTION_INFO_V1(pg_mul_int64_overflow);

Datum
pg_add_int64_overflow(PG_FUNCTION_ARGS)
{
	int64		v1 = PG_GETARG_INT64(0);
	int64		v2 = PG_GETARG_INT64(1);
	int64		result;

	PG_RETURN_BOOL(pg_add_s64_overflow(v1, v2, &result));
}

Datum
pg_sub_int64_overflow(PG_FUNCTION_ARGS)
{
	int64		v1 = PG_GETARG_INT64(0);
	int64		v2 = PG_GETARG_INT64(1);
	int64		result;

	PG_RETURN_BOOL(pg_sub_s64_overflow(v1, v2, &result));
}

Datum
pg_mul_int64_overflow(PG_FUNCTION_ARGS)
{
	int64		v1 = PG_GETARG_INT64(0);
	int64		v2 = PG_GETARG_INT64(1);
	int64		result;

	PG_RETURN_BOOL(pg_mul_s64_overflow(v1, v2, &result));
}

/* string to uint conversion functions */
PG_FUNCTION_INFO_V1(pg_string_to_int16);
PG_FUNCTION_INFO_V1(pg_string_to_int32);
PG_FUNCTION_INFO_V1(pg_string_to_int64);

Datum
pg_string_to_int16(PG_FUNCTION_ARGS)
{
	text	   *val_txt = PG_GETARG_TEXT_PP(0);
	char       *val = text_to_cstring(val_txt);
	pg_strtoint_status status = PG_STRTOINT_OK;
	int16		res;

	status = pg_strtoint16(val, &res);

	if (status == PG_STRTOINT_RANGE_ERROR)
		ereport(ERROR,
				(errcode(ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE),
				 errmsg("value \"%s\" is out of range for type %s",
						val, "smallint")));
	else if (status == PG_STRTOINT_SYNTAX_ERROR)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
				 errmsg("invalid input syntax for type %s: \"%s\"",
						"smallint", val)));

	PG_RETURN_INT16(res);
}

/*
 * String to int functions
 */
Datum
pg_string_to_int32(PG_FUNCTION_ARGS)
{
	text	   *val_txt = PG_GETARG_TEXT_PP(0);
	char       *val = text_to_cstring(val_txt);
	pg_strtoint_status status = PG_STRTOINT_OK;
	int32		res;

	status = pg_strtoint32(val, &res);

	if (status == PG_STRTOINT_RANGE_ERROR)
		ereport(ERROR,
				(errcode(ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE),
				 errmsg("value \"%s\" is out of range for type %s",
						val, "integer")));
	else if (status == PG_STRTOINT_SYNTAX_ERROR)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
				 errmsg("invalid input syntax for type %s: \"%s\"",
						"integer", val)));

	PG_RETURN_INT32(res);
}

/*
 * String to int functions
 */
Datum
pg_string_to_int64(PG_FUNCTION_ARGS)
{
	text	   *val_txt = PG_GETARG_TEXT_PP(0);
	char       *val = text_to_cstring(val_txt);
	pg_strtoint_status status = PG_STRTOINT_OK;
	int64		res;

	status = pg_strtoint64(val, &res);

	if (status == PG_STRTOINT_RANGE_ERROR)
		ereport(ERROR,
				(errcode(ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE),
				 errmsg("value \"%s\" is out of range for type %s",
						val, "bigint")));
	else if (status == PG_STRTOINT_SYNTAX_ERROR)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
				 errmsg("invalid input syntax for type %s: \"%s\"",
						"bigint", val)));

	PG_RETURN_INT64(res);
}
