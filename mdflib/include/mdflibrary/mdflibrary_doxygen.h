/**
 * @file mdflibrary_doxygen.h
 * @brief Doxygen module documentation for the MdfLibrary C++ wrapper.
 *
 * The `MdfLibrary` namespace is a convenience wrapper around the low-level
 * `mdf` API. It provides RAII-friendly classes and simpler accessors for use
 * in higher-level applications.
 *
 * @defgroup mdflibrary MdfLibrary Wrapper
 * @{
 *
 * Wrapper features:
 * - safe resource handling for `MdfFile`, `MdfChannelObserver` and related objects.
 * - easier string return semantics for C++ consumers.
 * - helper functions for group and channel enumeration.
 *
 * ASAM MDF concept mapping used in this wrapper:
 * - `MdfHeader` corresponds to the file root metadata block.
 * - `MdfDataGroup` corresponds to MDF Data Groups (DG).
 * - `MdfChannelGroup` corresponds to MDF Channel Groups (CG).
 * - `MdfChannel` corresponds to MDF Channels (CN).
 *
 * Typical read flow:
 * `MdfReader::Open()` -> `MdfReader::ReadHeader()` ->
 * `MdfReader::ReadMeasurementInfo()` -> `MdfReader::ReadData()` ->
 * `MdfChannelObserver::GetEngValue()`.
 *
 * Typical write flow:
 * `MdfWriter::CreateBusLogConfiguration()` -> `MdfWriter::InitMeasurement()` ->
 * `MdfWriter::StartMeasurement()` -> save messages ->
 * `MdfWriter::FinalizeMeasurement()`.
 *
 * ASAM MDF reference (public):
 * https://www.asam.net/standards/detail/mdf/wiki/
 *
 * @see MdfReader
 * @see MdfWriter
 * @see MdfFile
 * @see MdfChannelObserver
 *
 * @}
 */
#pragma once
