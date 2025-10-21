package com.example.ifc

import kotlin.test.Test
import kotlin.test.assertFailsWith
import kotlin.test.assertNotNull

class IfcJsonConverterTest {
    @Test
    fun `native methods throw when library missing`() {
        assertFailsWith<UnsatisfiedLinkError> {
            System.loadLibrary("ifcjsonconverter-nonexistent")
        }
    }

    @Test
    fun `transform options json`() {
        val options = TransformOptions(parallelism = 4, outputFormatting = "PRETTY")
        val json = options.toJson()
        assertNotNull(json)
    }
}
