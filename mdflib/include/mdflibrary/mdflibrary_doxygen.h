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
 * @}
 */
#pragma once
