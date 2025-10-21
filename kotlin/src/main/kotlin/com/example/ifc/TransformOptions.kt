package com.example.ifc

data class TransformOptions(
    val includeProperties: Boolean = true,
    val includeMaterials: Boolean = true,
    val includeTypes: Boolean = true,
    val schemaNormalization: String = "RAW",
    val dateTimeZone: String = "UTC",
    val parentStrategy: String = "SPATIAL_FIRST",
    val propertyIdStrategy: String = "GLOBALID_IF_EXISTS_ELSE_HASH",
    val materialIdStrategy: String = "GLOBALID_IF_EXISTS_ELSE_HASH",
    val parallelism: Int = 0,
    val outputFormatting: String = "COMPACT"
) {
    fun toJson(): String {
        // Minimal manual serialization to keep dependencies optional.
        val entries = listOf(
            "\"includeProperties\":$includeProperties",
            "\"includeMaterials\":$includeMaterials",
            "\"includeTypes\":$includeTypes",
            "\"schemaNormalization\":\"$schemaNormalization\"",
            "\"dateTimeZone\":\"$dateTimeZone\"",
            "\"parentStrategy\":\"$parentStrategy\"",
            "\"propertyIdStrategy\":\"$propertyIdStrategy\"",
            "\"materialIdStrategy\":\"$materialIdStrategy\"",
            "\"parallelism\":$parallelism",
            "\"outputFormatting\":\"$outputFormatting\""
        )
        return "{" + entries.joinToString(",") + "}"
    }
}
