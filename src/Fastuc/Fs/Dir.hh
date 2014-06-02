<?hh // strict
namespace Fastuc\Fs;

class Dir extends \Fastuc\Fs\File
{
	/**
	 * @param integer $mode
	 * @param bool $recursively
	 * @throws Exception
	 */
	public function create( int $mode = 0777, bool $recursively = true ) : void
	{
		if( false === mkdir( $this->getPathname(), $mode, $recursively ) )
		{
			throw new Exception( 'Could not create dir: ' . $this->getPathname() );
		}
	}

	/**
	 * @return bool
	 */
	public function deleteRecursively() : bool
	{
		$files = new \RecursiveIteratorIterator(
			new \RecursiveDirectoryIterator( $this->getPathname(), \RecursiveDirectoryIterator::SKIP_DOTS ),
			\RecursiveIteratorIterator::CHILD_FIRST
		);

		foreach( $files as $file )
		{
			$filePath = $file->getRealPath();
			if( $file->isDir() )
			{
				rmdir( $filePath );
			}
			else
			{
				if( false === @unlink( $filePath ) )
				{
					$lastError = error_get_last();
					throw new Exception( $lastError['message'] );
				}
			}
		}

		return rmdir( $this->getPathname() );
	}
}

