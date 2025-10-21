package com.example.ifc

import java.nio.file.Path

object IfcJsonConverter {
    init {
        try {
            System.loadLibrary("ifcjsonconverter")
        } catch (ex: UnsatisfiedLinkError) {
            // In development environments the native library may not be available yet.
            // Swallow the error so that integration tests using mock outputs can proceed.
        }
    }

    external fun initialize(optionsJson: String? = null)
    external fun shutdown()
    external fun transformFromFile(filePath: String, optionsJson: String? = null): String
    external fun transformFromBytes(ifcBytes: ByteArray, optionsJson: String? = null): ByteArray
    external fun getVersion(): String

    fun transformFileToString(path: Path, options: TransformOptions = TransformOptions()): String {
        val jsonBytes = transformFromFile(path.toString(), options.toJson())
        return jsonBytes
    }

    fun transformBytesToString(bytes: ByteArray, options: TransformOptions = TransformOptions()): String {
        val jsonBytes = transformFromBytes(bytes, options.toJson())
        return String(jsonBytes)
    }
}
