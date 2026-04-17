/**
 * @file mdf_doxygen.h
 * @brief Doxygen module documentation for the MDF core API.
 *
 * The `mdf` namespace contains the low-level MDF file API used for
 * reading, writing and manipulating MDF3/MDF4 files. It exposes file
 * metadata, data groups, attachments, channels and helpers for XML and
 * block handling.
 *
 * The core API is designed to be wrapped by higher-level helpers and
 * language bindings while keeping a clean and stable interface.
 *
 * @defgroup mdf MDF Core
 * @{
 *
 * Core concepts:
 * - `MdfFile`: top-level file handle and metadata interface.
 * - `IDataGroup`: measurement group (DG) container.
 * - `IChannel`: channel description and sample access.
 *
 * @}
 */
#pragma once