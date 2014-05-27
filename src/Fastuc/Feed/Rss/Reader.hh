<?hh // strict
namespace Fastuc\Feed\Rss;

class Reader
{
	/**
	 * @var string
	 */
	private string $url;

	/**
	 * @param string $url
	 */
	public function __construct( string $url )
	{
		$this->url = $url;
	}

	/**
	 * @return array
	 */
	public function getItems() : array
	{
		$items = array();

		$content = @file_get_contents( $this->url );
		if( empty( $content ) )
		{
			trigger_error( 'Unable to get remote content from: ' . $this->url, E_USER_NOTICE );
			return $items;
		}

		$xml = simplexml_load_string( $content );
		if( !isset( $xml->channel->item ) )
		{
			trigger_error( 'Invalid content retrieved from: ' . $this->url, E_USER_NOTICE );
			return $items;
		}

		foreach( $xml->channel->item as $item )
		{
			$items[] = array(
				'title' => strval( $item->title ),
				'url' => strval( $item->link ),
			);
		}

		return $items;
	}
}

