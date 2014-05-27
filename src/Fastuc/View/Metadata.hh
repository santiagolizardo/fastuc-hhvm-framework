<?hh // strict
namespace Fastuc\View;

class Metadata
{
	/**
	 * @param \Fastuc\View\Base $view
	 * @param string $section
	 * @param array $params
	 */
	public static function fillView( \Fastuc\View\Base $view, string $section, array $params = array() ) : void
	{
		$metadataConfig = new \Fastuc\Config\File( 'metadata' );
		$metadata = $metadataConfig->getValue();

		if( !isset( $metadata[ $section ] ) )
		{
			return;
		}

		$metadata = $metadata[ $section ];

		if( isset( $metadata['title'] ) )
		{
			$title = $metadata['title']( $params );
			$view->setTitle( $title );
		}

		if( isset( $metadata['description'] ) )
		{
			$description = $metadata['description']( $params );
			$view->setMeta( 'description', $description );
		}

		if( isset( $metadata['keywords'] ) )
		{
			$keywords = $metadata['keywords']( $params );
			$view->setMeta( 'keywords', $keywords );
		}
	}
}

