<?hh // strict
namespace Fastuc\Cache;

/**
 * A cache layer implementation over regular filesystem (disk).
 */
class Disk implements ICache
{
	/**
	 * @var int Number of seconds to expire.
	 */
	private int $expirationTime;

	/**
	 * @var string Directory path where the cache objects are going to be persisted.
	 */
	private string $directory;

	/**
	 * @param int $expirationDate Number of seconds to expire.
	 */
	public function __construct( int $expirationTime = 3600 )
	{
		$this->expirationTime = $expirationTime;
		$this->directory = __DIR__;
	}

	/**
	 * @return int
	 */
	public function getExpirationTime() : int
	{
		return $this->expirationTime;
	}

	/**
	 * @param string $directory
	 */
	public function setDirectory( string $directory ) : void
	{
		$this->directory = $directory;
	}

	/**
	 * @return string
	 */
	public function getDirectory() : string
	{
		return $this->directory;
	}

	/**
	 * Builds a path to the directory where the cached object will be stored.
	 *
	 * @param string $key Key of the cached object.
	 * @return string
	 */
	private function buildPath( string $key ) : string
	{
		return $this->directory . DIRECTORY_SEPARATOR . $key;
	}

	/**
	 * @param string $key
	 * @return \Fastuc\Fs\File
	 */
	private function getFilePathForKey( string $key ) : \Fastuc\Fs\File
	{
		$path = $this->buildPath( $key );
		return new \Fastuc\Fs\File( $path );
	}

	/**
	 * @param string $key
	 * @return bool
	 */
	public function check( string $key ) : bool
	{
		$file = $this->getFilePathForKey( $key );
		if( !$file->exists() )
		{
			return false;
		}

		if( time() - filemtime( $file ) <= $this->expirationTime )
		{
			return true;
		}

		unlink( $file );

		return false;
	}

	/**
	 * @param string $key Key of the cached object
	 * @return mixed|null
	 */
	public function get( string $key ) : mixed
	{
		if( $this->check( $key ) )
		{
			$file = $this->getFilePathForKey( $key );
			return $file->getContents();
		}
		return null;
	}

	/**
	 * Adds (replaces) an object in the cache.
	 *
	 * @param string $key Key of the cached object.
	 * @param mixed $value Value to be cached.
	 * @throws \Fastuc\Cache\Exception if the value could not be saved.
	 */
	public function set( string $key, mixed $value ) : void
	{
		$file = $this->getFilePathForKey( $key );
		if( $file->exists() && !$file->isWritable() )
		{
			throw new Exception( 'Destination file is not writable: ' . $file->getPathname(), E_USER_WARNING );
		}
		$file->putContents( $value );
	}
}

