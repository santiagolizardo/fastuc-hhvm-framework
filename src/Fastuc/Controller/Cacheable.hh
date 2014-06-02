<?hh // strict
namespace Fastuc\Controller;

abstract class Cacheable extends Base 
{
	/**
	 * @param \Fastuc\Input\Http $params
	 */
	abstract public function processGet( \Fastuc\Input\Http $params );

	/**
	 * @param \Fastuc\Input\Http $params
	 */
	public function doGet( \Fastuc\Input\Http $params ) : void
	{
		$cachedOutput = $this->getCacheContent();
		if( false !== $cachedOutput )
		{
			$this->sendResponse( $cachedOutput );
			return;
		}

		$output = $this->processGet( $params );
		$this->saveCacheContent( $output );

		$this->sendResponse( $output );
	}

	/**
	 * @param string|array $output
	 */
	private function sendResponse( mixed $output ) : void
	{
		if( is_array( $output ) )
		{
			$this->response->setContentType( $output['contentType'] );
			$this->response->write( $output['content'] );
		}
		elseif( is_string( $output ) )
		{
			$this->response->write( $output );
		}
	}

	/**
	 * @return null
	 */
	protected function getCacheKey() : string
	{
		return null;
	}

	/**
	 * @return integer Defaults to 6 hours.
	 */
	protected function getCacheExpiration() : int
	{
		return ( 60 * 60 * 6 );
	}

	/**
	 * @return mixed
	 */
	protected function getCacheContent() : string
	{
		$cacheServer = new \Fastuc\Cache\Volatile;
		return $cacheServer->get( $this->getCacheKey() );
	}

	/**
	 * @param mixed $content
	 */
	protected function saveCacheContent( mixed $content ) : void
	{
		$cacheServer = new \Fastuc\Cache\Volatile;
		$cacheServer->set( $this->getCacheKey(), $content, $this->getCacheExpiration() );
	}
}

