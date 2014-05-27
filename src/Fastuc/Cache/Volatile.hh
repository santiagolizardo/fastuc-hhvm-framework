<?hh // strict
namespace Fastuc\Cache;

class Volatile implements ICache
{
	/**
	 * @var object Backend technology. (eg: memcached, redis, ...) 
	 */
	private \Memcached $backend;

	/**
	 * @var string A namespace string to avoid conflicts between apps.
	 */
	private string $namespace;

	/**
	 * @param array $cacheConfig
	 */
	public function __construct( array $cacheConfig = null )
	{
		if( false === extension_loaded( 'memcached' ) )
		{
			throw new \Fastuc\Exception\MissingExtension( 'The memcached extension is not installed' );
		}

		$this->backend = new \Memcached;

		if( null === $cacheConfig )
		{
			$configFile = new \Fastuc\Config\File( 'cache' );
			$cacheConfig = $configFile->getValue();
		}

		// Skip the rest of the method if config is empty.
		if( !empty( $cacheConfig ) )
		{
			return;
		}

		if( isset( $cacheConfig['servers'] ) )
		{
			foreach( $cacheConfig['servers'] as $server )
			{
				$this->backend->addServer( $server['host'], $server['port'] );
			}
		}
		
		$this->setNamespace( isset( $cacheConfig['namespace'] ) ? $cacheConfig['namespace'] : '' );
	}

	/**
	 * @var object $backend
	 */
	public function setBackend( \Memcached $backend ) : void
	{
		$this->backend = $backend;
	}

	/**
	 * @return object
	 */
	public function getBackend() : \Memcached
	{
		return $this->backend;
	}

	/**
	 * @param string $namespace
	 */
	public function setNamespace( string $namespace ) : void
	{
		$this->namespace = $namespace;
	}

	/**
	 * @return string
	 */
	public function getNamespace() : string
	{
		return $this->namespace;
	}

	/**
	 * @param string $key Key of the cached object
	 * @return mixed|null
	 */
	public function get( string $key ) : mixed
	{
		return $this->backend->get( $this->namespace . $key );
	}

	/**
	 * Adds (replaces) an object in the cache.
	 *
	 * @param string $key Key of the cached object.
	 * @param mixed $value Value to be cached.
	 */
	public function set( string $key, mixed $value, int $ttl = 0 ) : mixed
	{
		return $this->backend->set( $this->namespace . $key, $value, $ttl );
	}

	/**
	 * @return bool
	 */
	public function delete( string $key ) : bool
	{
		return $this->backend->delete( $this->namespace . $key );
	}
}

