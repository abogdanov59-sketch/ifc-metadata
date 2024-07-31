using Newtonsoft.Json;

namespace Bingosoft.Net.IfcMetadata
{
    /// <summary>
    ///   The MetaObject is used to serialise the building elements within the IFC
    ///   model. It is a representation of a single element (e.g. IfcProject,
    ///   IfcStorey, IfcWindow, etc.).
    /// </summary>
    public struct Metadata
    {
        /// <summary>
        ///   The GlobalId of the building element
        /// </summary>
        [JsonProperty("id")]
        public string Id { get; set; }

        /// <summary>
        ///   The Name of the building element
        /// </summary>
        [JsonProperty("name")]
        public string Name { get; set; }

        /// <summary>
        ///   The IFC type of the building element, e.g. 'IfcStandardWallCase'
        /// </summary>
        [JsonProperty("type")]
        public string @Type { get; set; }

        /// <summary>
        ///   The GlobalId of the parent element if any.
        /// </summary>
        [JsonProperty("parent")]
        public string Parent { get; set; }

        [JsonProperty("properties")]
        public string[] PropertyIds { get; set; }

        [JsonProperty("material_id")]
        public string Material { get; set; }

        [JsonProperty("type_id")]
        public string TypeId { get; set; }
    }
}