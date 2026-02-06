
namespace cardozo {

    enum class MatrixMetadata
    {
        Invalid = -1,
        Symmetric = 1
    };

    inline MatrixMetadata operator|(MatrixMetadata a, MatrixMetadata b)
    {
        return static_cast<MatrixMetadata>(static_cast<int>(a) | static_cast<int>(b));
    }

}
