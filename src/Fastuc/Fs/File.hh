<?hh // strict
namespace Fastuc\Fs;

class File extends \SplFileInfo
{
	/**
	 * @return bool
	 */
	public function exists() : bool
	{
		return file_exists( $this->getPathname() );
	}

	/**
	 * Save the content of the parameter to the current path.
	 *
	 * @param string $content
	 * @return int Number of bytes written, or false on failure.
	 */
	public function putContents( string $content ) : int
	{
		return file_put_contents( $this->getPathname(), $content );
	}

	/**
	 * @return string
	 */
	public function getContents() : string
	{
		return file_get_contents( $this->getPathname() );
	}

	/**
	 * @param string $filePath
	 */
	public function copyFrom( string $filePath ) : string
	{
		return copy( $filePath, $this->getPathname() );
	}

	/**
	 * @return bool
	 */
	public function touch() : bool
	{
		if( false === touch( $this->getPathname() ) )
		{
			throw new Exception( 'File could not be touched: ' . $this->getPathname() );
		}
		return true;
	}

	/**
	 * @return bool
	 */
	public function delete() : bool
	{
		if( false === @unlink( $this->getPathname() ) )
		{
			throw new Exception( 'File could not be deleted: ' . $this->getPathname() );
		}
		return true;

	}
}

