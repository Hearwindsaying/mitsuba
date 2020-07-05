#include <mitsuba/render/scene.h>

MTS_NAMESPACE_BEGIN

class SHIntegrator : public SamplingIntegrator 
{
public:
    SHIntegrator(const Properties &props) : SamplingIntegrator(props) 
    {
        Spectrum defaultColor;
        defaultColor.fromLinearRGB(0.2f, 0.5f, 0.2f);
        this->m_color = props.getSpectrum("color", defaultColor);
    }

    /* Serialization and unserialization support. */
    SHIntegrator(Stream *stream, InstanceManager *manager) : SamplingIntegrator(stream, manager)
    {
        this->m_color = Spectrum(stream);
    }

    void serialize(Stream *stream, InstanceManager *manager) const
    {
        SamplingIntegrator::serialize(stream, manager);
        this->m_color.serialize(stream);
    }

    Spectrum Li(const RayDifferential &ray, RadianceQueryRecord &rRec) const
    {
        return m_color;
    }

private:
    Spectrum m_color;

    MTS_DECLARE_CLASS()
};

MTS_IMPLEMENT_CLASS_S(SHIntegrator, false, SamplingIntegrator)
MTS_EXPORT_PLUGIN(SHIntegrator, "Spherical Harmonics Lighting integrator");
MTS_NAMESPACE_END