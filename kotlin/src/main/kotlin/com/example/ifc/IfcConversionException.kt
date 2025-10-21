package com.example.ifc

class IfcConversionException(
    val code: String,
    override val message: String?
) : RuntimeException(message)
